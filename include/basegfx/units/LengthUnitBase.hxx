/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <sal/types.h>

#include <ostream>
#include <cmath>

namespace gfx
{
namespace
{
constexpr sal_Int64 constFactor_hmm_to_EMU = 360ll;
constexpr sal_Int64 constFactor_mm_to_EMU = constFactor_hmm_to_EMU * 100ll;
constexpr sal_Int64 constFactor_cm_to_EMU = constFactor_hmm_to_EMU * 1000ll;
constexpr sal_Int64 constFactor_m_to_EMU = constFactor_hmm_to_EMU * 100000ll;

constexpr sal_Int64 constFactor_twip_to_EMU = 635ll;
constexpr sal_Int64 constFactor_in_to_EMU = constFactor_twip_to_EMU * 1440ll;
constexpr sal_Int64 constFactor_pt_to_EMU = constFactor_twip_to_EMU * 20ll;
constexpr sal_Int64 constFactor_px_to_EMU = constFactor_twip_to_EMU * 15ll;

} // end anonymous namespace

template <typename TYPE> class LengthUnitBase
{
private:
    // value in EMU units
    TYPE m_nValue;

    constexpr explicit LengthUnitBase(TYPE nValue)
        : m_nValue(nValue)
    {
    }

public:
    static constexpr LengthUnitBase min() { return LengthUnitBase(SAL_MIN_INT64); }

    static constexpr LengthUnitBase max() { return LengthUnitBase(SAL_MAX_INT64); }

    template <typename INPUT_TYPE> static constexpr LengthUnitBase cm(INPUT_TYPE nValue)
    {
        return LengthUnitBase(TYPE(gfx::constFactor_cm_to_EMU * nValue));
    }

    template <typename INPUT_TYPE> static constexpr LengthUnitBase mm(INPUT_TYPE nValue)
    {
        return LengthUnitBase(TYPE(gfx::constFactor_mm_to_EMU * nValue));
    }

    template <typename INPUT_TYPE> static constexpr LengthUnitBase hmm(INPUT_TYPE nValue)
    {
        return LengthUnitBase(TYPE(gfx::constFactor_hmm_to_EMU * nValue));
    }

    template <typename INPUT_TYPE> static constexpr LengthUnitBase in(INPUT_TYPE nValue)
    {
        return LengthUnitBase(TYPE(gfx::constFactor_in_to_EMU * nValue));
    }

    template <typename INPUT_TYPE> static constexpr LengthUnitBase twip(INPUT_TYPE nValue)
    {
        return LengthUnitBase(TYPE(gfx::constFactor_twip_to_EMU * nValue));
    }

    template <typename INPUT_TYPE> static constexpr LengthUnitBase pt(INPUT_TYPE nValue)
    {
        return LengthUnitBase(TYPE(gfx::constFactor_pt_to_EMU * nValue));
    }

    template <typename INPUT_TYPE> static constexpr LengthUnitBase px(INPUT_TYPE nValue)
    {
        return LengthUnitBase(TYPE(gfx::constFactor_px_to_EMU * nValue));
    }

    template <typename INPUT_TYPE> static constexpr LengthUnitBase emu(INPUT_TYPE nValue)
    {
        return LengthUnitBase(TYPE(nValue));
    }

    constexpr explicit LengthUnitBase()
        : m_nValue(0)
    {
    }

    constexpr explicit operator TYPE() const { return m_nValue; }

    constexpr LengthUnitBase& operator+=(LengthUnitBase const& rhs)
    {
        m_nValue += rhs.m_nValue;
        return *this;
    }

    constexpr LengthUnitBase& operator-=(LengthUnitBase const& rhs)
    {
        m_nValue -= rhs.m_nValue;
        return *this;
    }

    constexpr LengthUnitBase& operator*=(TYPE const& rhs)
    {
        m_nValue *= rhs;
        return *this;
    }

    constexpr LengthUnitBase& operator/=(TYPE const& rhs)
    {
        m_nValue /= rhs;
        return *this;
    }

    constexpr LengthUnitBase& operator-()
    {
        m_nValue = -m_nValue;
        return *this;
    }

    constexpr bool operator<(LengthUnitBase const& other) const
    {
        return m_nValue < other.m_nValue;
    }
    constexpr bool operator<=(LengthUnitBase const& other) const
    {
        return m_nValue <= other.m_nValue;
    }
    constexpr bool operator>(LengthUnitBase const& other) const
    {
        return m_nValue > other.m_nValue;
    }
    constexpr bool operator>=(LengthUnitBase const& other) const
    {
        return m_nValue >= other.m_nValue;
    }
    constexpr bool operator==(LengthUnitBase const& other) const
    {
        return m_nValue == other.m_nValue;
    }
    constexpr bool operator!=(LengthUnitBase const& other) const
    {
        return m_nValue != other.m_nValue;
    }

    constexpr TYPE raw() const { return m_nValue; }

    double as_hmm() const { return m_nValue / double(constFactor_hmm_to_EMU); }
    double as_mm() const { return m_nValue / double(constFactor_mm_to_EMU); }
    double as_cm() const { return m_nValue / double(constFactor_cm_to_EMU); }
    double as_m() const { return m_nValue / double(constFactor_m_to_EMU); }
    double as_twip() const { return m_nValue / double(constFactor_twip_to_EMU); }
    double as_in() const { return m_nValue / double(constFactor_in_to_EMU); }
    double as_pt() const { return m_nValue / double(constFactor_pt_to_EMU); }
    double as_px() const { return m_nValue / double(constFactor_px_to_EMU); }
    double as_emu() const { return double(m_nValue); }
};

template <typename T>
inline LengthUnitBase<T> operator+(LengthUnitBase<T> lhs, const LengthUnitBase<T>& rhs)
{
    return lhs += rhs;
}

template <typename T>
inline LengthUnitBase<T> operator-(LengthUnitBase<T> lhs, const LengthUnitBase<T>& rhs)
{
    return lhs -= rhs;
}

/// Multiplication of a length unit with a scalar value.
/// example 1cm * 2 = 2cm
template <typename T> inline LengthUnitBase<T> operator*(LengthUnitBase<T> lhs, const long rhs)
{
    return lhs *= rhs;
}

/// Division of a length unit with a scalar value.
/// example 1cm / 2 = 0.5cm
template <typename T> inline LengthUnitBase<T> operator/(LengthUnitBase<T> lhs, const long rhs)
{
    return lhs /= rhs;
}

/// Division of 2 length units, which results in a ratio.
/// example 1cm / 2cm = 0.5
template <typename T> inline double operator/(LengthUnitBase<T> lhs, const LengthUnitBase<T> rhs)
{
    return lhs.raw() / double(rhs.raw());
}

} // end namespace gfx
