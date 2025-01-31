/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <comphelper/sequence.hxx>
#include <sal/log.hxx>

#include <doc.hxx>
#include <docsh.hxx>
#include <IDocumentMarkAccess.hxx>

#include "vbaformfield.hxx"
#include "vbaformfields.hxx"
#include "wordvbahelper.hxx"

using namespace ::ooo::vba;
using namespace ::com::sun::star;

// Helper function to access the fieldmarks
// @param rIndex serves multiple purposes
//        [in] -1 to indicate searching using the provided name, SAL_MAX_INT32 for totals
//        [out] rIndex indicates the found index, or the total number of fieldmarks
static sw::mark::IFieldmark* lcl_getFieldmark(std::string_view rName, sal_Int32& rIndex,
                                              const css::uno::Reference<frame::XModel>& xModel,
                                              uno::Sequence<OUString>* pElementNames = nullptr)
{
    SwDoc* pDoc = word::getDocShell(xModel)->GetDoc();
    if (!pDoc)
        return nullptr;

    IDocumentMarkAccess* pMarkAccess = pDoc->getIDocumentMarkAccess();
    if (!pMarkAccess)
        return nullptr;

    sal_Int32 nCounter = 0;
    std::vector<OUString> vElementNames;
    IDocumentMarkAccess::iterator aIter = pMarkAccess->getFieldmarksBegin();
    while (aIter != pMarkAccess->getFieldmarksEnd())
    {
        switch (IDocumentMarkAccess::GetType(**aIter))
        {
            case IDocumentMarkAccess::MarkType::CHECKBOX_FIELDMARK:
            case IDocumentMarkAccess::MarkType::DROPDOWN_FIELDMARK:
            case IDocumentMarkAccess::MarkType::TEXT_FIELDMARK:
            {
                if (rIndex < 0
                    && (*aIter)->GetName().equalsIgnoreAsciiCase(OUString::fromUtf8(rName)))
                {
                    rIndex = nCounter;
                    return dynamic_cast<sw::mark::IFieldmark*>(*aIter);
                }
                else if (rIndex == nCounter)
                    return dynamic_cast<sw::mark::IFieldmark*>(*aIter);

                ++nCounter;
                if (pElementNames)
                    vElementNames.push_back((*aIter)->GetName());
                break;
            }
            default:;
        }
        aIter++;
    }
    rIndex = nCounter;
    if (pElementNames)
        *pElementNames = comphelper::containerToSequence(vElementNames);
    return nullptr;
}

namespace
{
class FormFieldsEnumWrapper : public EnumerationHelper_BASE
{
    uno::Reference<container::XIndexAccess> mxIndexAccess;
    sal_Int32 nIndex;

public:
    explicit FormFieldsEnumWrapper(uno::Reference<container::XIndexAccess> xIndexAccess)
        : mxIndexAccess(std::move(xIndexAccess))
        , nIndex(0)
    {
    }
    virtual sal_Bool SAL_CALL hasMoreElements() override
    {
        return (nIndex < mxIndexAccess->getCount());
    }

    virtual uno::Any SAL_CALL nextElement() override
    {
        if (nIndex < mxIndexAccess->getCount())
        {
            return mxIndexAccess->getByIndex(nIndex++);
        }
        throw container::NoSuchElementException();
    }
};

class FormFieldCollectionHelper
    : public ::cppu::WeakImplHelper<container::XNameAccess, container::XIndexAccess,
                                    container::XEnumerationAccess>
{
private:
    uno::Reference<XHelperInterface> mxParent;
    uno::Reference<uno::XComponentContext> mxContext;
    css::uno::Reference<frame::XModel> mxModel;
    sw::mark::IFieldmark* m_pCache;

public:
    /// @throws css::uno::RuntimeException
    FormFieldCollectionHelper(css::uno::Reference<ov::XHelperInterface> xParent,
                              css::uno::Reference<css::uno::XComponentContext> xContext,
                              css::uno::Reference<frame::XModel> xModel)
        : mxParent(std::move(xParent))
        , mxContext(std::move(xContext))
        , mxModel(std::move(xModel))
        , m_pCache(nullptr)
    {
    }

    // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() override
    {
        sal_Int32 nCount = SAL_MAX_INT32;
        lcl_getFieldmark("", nCount, mxModel);
        return nCount == SAL_MAX_INT32 ? 0 : nCount;
    }

    virtual uno::Any SAL_CALL getByIndex(sal_Int32 Index) override
    {
        m_pCache = lcl_getFieldmark("", Index, mxModel);
        if (!m_pCache)
            throw css::lang::IndexOutOfBoundsException();

        return uno::Any(uno::Reference<word::XFormField>(
            new SwVbaFormField(mxParent, mxContext, mxModel, *m_pCache)));
    }

    // XNameAccess
    virtual uno::Sequence<OUString> SAL_CALL getElementNames() override
    {
        sal_Int32 nCount = SAL_MAX_INT32;
        uno::Sequence<OUString> aSeq;
        lcl_getFieldmark("", nCount, mxModel, &aSeq);
        return aSeq;
    }

    virtual uno::Any SAL_CALL getByName(const OUString& aName) override
    {
        if (!hasByName(aName))
            throw container::NoSuchElementException();

        return uno::Any(uno::Reference<word::XFormField>(
            new SwVbaFormField(mxParent, mxContext, mxModel, *m_pCache)));
    }

    virtual sal_Bool SAL_CALL hasByName(const OUString& aName) override
    {
        sal_Int32 nCount = -1;
        m_pCache = lcl_getFieldmark(aName.toUtf8(), nCount, mxModel);
        return m_pCache != nullptr;
    }

    // XElementAccess
    virtual uno::Type SAL_CALL getElementType() override
    {
        return cppu::UnoType<word::XFormField>::get();
    }

    virtual sal_Bool SAL_CALL hasElements() override { return getCount() != 0; }

    // XEnumerationAccess
    virtual uno::Reference<container::XEnumeration> SAL_CALL createEnumeration() override
    {
        return new FormFieldsEnumWrapper(this);
    }
};
}

SwVbaFormFields::SwVbaFormFields(const uno::Reference<XHelperInterface>& xParent,
                                 const uno::Reference<uno::XComponentContext>& xContext,
                                 const uno::Reference<frame::XModel>& xModel)
    : SwVbaFormFields_BASE(xParent, xContext,
                           uno::Reference<container::XIndexAccess>(
                               new FormFieldCollectionHelper(xParent, xContext, xModel)))
{
}

sal_Bool SwVbaFormFields::getShaded()
{
    SAL_INFO("sw.vba", "SwVbaFormFields::getShaded stub");
    return false;
}

void SwVbaFormFields::setShaded(sal_Bool /*bSet*/)
{
    SAL_INFO("sw.vba", "SwVbaFormFields::setShaded stub");
}

// uno::Reference<ooo::vba::word::XFormField> SwVbaFormFields::Add(const css::uno::Any& Range,
//                                                                 sal_Int32 Type)
// {
//     sw::mark::IFieldmark* pFieldmark = nullptr;
//     switch (Type)
//     {
//         case ooo::vba::word::WdFieldType::wdFieldFormCheckBox:
//             break;
//         case ooo::vba::word::WdFieldType::wdFieldFormDropDown:
//             break;
//         case ooo::vba::word::WdFieldType::wdFieldFormTextInput:
//         default:;
//     }
//
//     return uno::Reference<ooo::vba::word::XFormField>(
//         new SwVbaFormField(mxParent, mxContext, m_xModel, *pFieldmark));
// }

// XEnumerationAccess
uno::Type SwVbaFormFields::getElementType() { return cppu::UnoType<word::XFormField>::get(); }

uno::Reference<container::XEnumeration> SwVbaFormFields::createEnumeration()
{
    return new FormFieldsEnumWrapper(m_xIndexAccess);
}

uno::Any SwVbaFormFields::createCollectionObject(const css::uno::Any& aSource) { return aSource; }

OUString SwVbaFormFields::getServiceImplName() { return "SwVbaFormFields"; }

css::uno::Sequence<OUString> SwVbaFormFields::getServiceNames()
{
    static uno::Sequence<OUString> const sNames{ "ooo.vba.word.FormFields" };
    return sNames;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
