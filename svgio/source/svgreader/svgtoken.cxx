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

#include <svgtoken.hxx>
#include <frozen/map.h>

namespace svgio::svgreader
{
        constexpr const std::u16string_view constToken_Width = u"width";
        constexpr const std::u16string_view constToken_Height = u"height";
        constexpr const std::u16string_view constToken_ViewBox = u"viewBox";
        constexpr const std::u16string_view constTokenLowercase_ViewBox = u"viewbox";
        constexpr const std::u16string_view constToken_Transform = u"transform";
        constexpr const std::u16string_view constToken_Style = u"style";
        constexpr const std::u16string_view constToken_Display = u"display"; // #i121656#
        constexpr const std::u16string_view constToken_D = u"d";
        constexpr const std::u16string_view constToken_X = u"x";
        constexpr const std::u16string_view constToken_Y = u"y";
        constexpr const std::u16string_view constToken_Xmlns = u"xmlns";
        constexpr const std::u16string_view constToken_Version = u"version";
        constexpr const std::u16string_view constToken_Id = u"id";
        constexpr const std::u16string_view constToken_Rx = u"rx";
        constexpr const std::u16string_view constToken_Ry = u"ry";
        constexpr const std::u16string_view constToken_Points = u"points";
        constexpr const std::u16string_view constToken_Dx = u"dx";
        constexpr const std::u16string_view constToken_Dy = u"dy";
        constexpr const std::u16string_view constToken_Rotate = u"rotate";
        constexpr const std::u16string_view constToken_TextLength = u"textLength";
        constexpr const std::u16string_view constTokenLowercase_TextLength = u"textlength";
        constexpr const std::u16string_view constToken_LengthAdjust = u"lengthAdjust";
        constexpr const std::u16string_view constTokenLowercase_LengthAdjust = u"lengthadjust";
        constexpr const std::u16string_view constToken_Font = u"font";
        constexpr const std::u16string_view constToken_FontFamily = u"font-family";
        constexpr const std::u16string_view constToken_FontSize = u"font-size";
        constexpr const std::u16string_view constToken_FontSizeAdjust = u"font-size-adjust";
        constexpr const std::u16string_view constToken_FontStretch = u"font-stretch";
        constexpr const std::u16string_view constToken_FontStyle = u"font-style";
        constexpr const std::u16string_view constToken_FontVariant = u"font-variant";
        constexpr const std::u16string_view constToken_FontWeight = u"font-weight";
        constexpr const std::u16string_view constToken_Direction = u"direction";
        constexpr const std::u16string_view constToken_LetterSpacing = u"letter-spacing";
        constexpr const std::u16string_view constToken_TextDecoration = u"text-decoration";
        constexpr const std::u16string_view constToken_UnicodeBidi = u"unicode-bidi";
        constexpr const std::u16string_view constToken_WordSpacing = u"word-spacing";
        constexpr const std::u16string_view constToken_Tspan = u"tspan";
        constexpr const std::u16string_view constToken_Tref = u"tref";
        constexpr const std::u16string_view constToken_TextPath = u"textPath";
        constexpr const std::u16string_view constTokenLowercase_TextPath = u"textpath";
        constexpr const std::u16string_view constToken_StartOffset = u"startOffset";
        constexpr const std::u16string_view constTokenLowercase_StartOffset = u"startoffset";
        constexpr const std::u16string_view constToken_Method = u"method";
        constexpr const std::u16string_view constToken_Spacing = u"spacing";
        constexpr const std::u16string_view constToken_TextAlign = u"text-align";
        constexpr const std::u16string_view constToken_PathLength = u"pathLength";
        constexpr const std::u16string_view constTokenLowercase_PathLength = u"pathlength";
        constexpr const std::u16string_view constToken_Type = u"type";
        constexpr const std::u16string_view constToken_Class = u"class";
        constexpr const std::u16string_view constToken_TextAnchor = u"text-anchor";
        constexpr const std::u16string_view constToken_XmlSpace = u"xml:space";
        constexpr const std::u16string_view constToken_Color = u"color";
        constexpr const std::u16string_view constToken_ClipPathNode = u"clipPath";
        constexpr const std::u16string_view constTokenLowercase_ClipPathNode = u"clippath";
        constexpr const std::u16string_view constToken_ClipPathProperty = u"clip-path";
        constexpr const std::u16string_view constToken_Mask = u"mask";
        constexpr const std::u16string_view constToken_ClipPathUnits = u"clipPathUnits";
        constexpr const std::u16string_view constTokenLowercase_ClipPathUnits = u"clippathunits";
        constexpr const std::u16string_view constToken_MaskUnits = u"maskUnits";
        constexpr const std::u16string_view constTokenLowercase_MaskUnits = u"maskunits";
        constexpr const std::u16string_view constToken_MaskContentUnits = u"maskContentUnits";
        constexpr const std::u16string_view constTokenLowercase_MaskContentUnits = u"maskcontentunits";
        constexpr const std::u16string_view constToken_ClipRule = u"clip-rule";
        constexpr const std::u16string_view constToken_Marker = u"marker";
        constexpr const std::u16string_view constToken_MarkerStart = u"marker-start";
        constexpr const std::u16string_view constToken_MarkerMid = u"marker-mid";
        constexpr const std::u16string_view constToken_MarkerEnd = u"marker-end";
        constexpr const std::u16string_view constToken_RefX = u"refX";
        constexpr const std::u16string_view constToken_RefY = u"refY";
        constexpr const std::u16string_view constToken_MarkerUnits = u"markerUnits";
        constexpr const std::u16string_view constTokenLowercase_MarkerUnits = u"markerunits";
        constexpr const std::u16string_view constToken_MarkerWidth = u"markerWidth";
        constexpr const std::u16string_view constTokenLowercase_MarkerWidth = u"markerwidth";
        constexpr const std::u16string_view constToken_MarkerHeight = u"markerHeight";
        constexpr const std::u16string_view constTokenLowercase_MarkerHeight = u"markerheight";
        constexpr const std::u16string_view constToken_Orient = u"orient";
        constexpr const std::u16string_view constToken_Pattern = u"pattern";
        constexpr const std::u16string_view constToken_PatternUnits = u"patternUnits";
        constexpr const std::u16string_view constTokenLowercase_PatternUnits = u"patternunits";
        constexpr const std::u16string_view constToken_PatternContentUnits = u"patternContentUnits";
        constexpr const std::u16string_view constTokenLowercase_PatternContentUnits = u"patterncontentunits";
        constexpr const std::u16string_view constToken_PatternTransform = u"patternTransform";
        constexpr const std::u16string_view constTokenLowercase_PatternTransform = u"patterntransform";
        constexpr const std::u16string_view constToken_Opacity = u"opacity";
        constexpr const std::u16string_view constToken_Visibility = u"visibility";
        constexpr const std::u16string_view constToken_Title = u"title";
        constexpr const std::u16string_view constToken_Desc = u"desc";

        constexpr const std::u16string_view constToken_PreserveAspectRatio = u"preserveAspectRatio";
        constexpr const std::u16string_view constTokenLowercase_PreserveAspectRatio = u"preserveaspectratio";
        constexpr const std::u16string_view constToken_Defer = u"defer";
        constexpr const std::u16string_view constToken_None = u"none";
        constexpr const std::u16string_view constToken_XMinYMin = u"xMinYMin";
        constexpr const std::u16string_view constTokenLowercase_XMinYMin = u"xminymin";
        constexpr const std::u16string_view constToken_XMidYMin = u"xMidYMin";
        constexpr const std::u16string_view constTokenLowercase_XMidYMin = u"xmidymin";
        constexpr const std::u16string_view constToken_XMaxYMin = u"xMaxYMin";
        constexpr const std::u16string_view constTokenLowercase_XMaxYMin = u"xmaxymin";
        constexpr const std::u16string_view constToken_XMinYMid = u"xMinYMid";
        constexpr const std::u16string_view constTokenLowercase_XMinYMid = u"xminymid";
        constexpr const std::u16string_view constToken_XMidYMid = u"xMidYMid";
        constexpr const std::u16string_view constTokenLowercase_XMidYMid = u"xmidymid";
        constexpr const std::u16string_view constToken_XMaxYMid = u"xMaxYMid";
        constexpr const std::u16string_view constTokenLowercase_XMaxYMid = u"xmaxymid";
        constexpr const std::u16string_view constToken_XMinYMax = u"xMinYMax";
        constexpr const std::u16string_view constTokenLowercase_XMinYMax = u"xminymax";
        constexpr const std::u16string_view constToken_XMidYMax = u"xMidYMax";
        constexpr const std::u16string_view constTokenLowercase_XMidYMax = u"xmidymax";
        constexpr const std::u16string_view constToken_XMaxYMax = u"xMaxYMax";
        constexpr const std::u16string_view constTokenLowercase_XMaxYMax = u"xmaxymax";
        constexpr const std::u16string_view constToken_Meet = u"meet";
        constexpr const std::u16string_view constToken_Slice = u"slice";

        constexpr const std::u16string_view constToken_Defs = u"defs";
        constexpr const std::u16string_view constToken_G = u"g";
        constexpr const std::u16string_view constToken_Svg = u"svg";
        constexpr const std::u16string_view constToken_Symbol = u"symbol";
        constexpr const std::u16string_view constToken_Use = u"use";
        constexpr const std::u16string_view constToken_A = u"a";

        constexpr const std::u16string_view constToken_Circle = u"circle";
        constexpr const std::u16string_view constToken_Ellipse = u"ellipse";
        constexpr const std::u16string_view constToken_Line = u"line";
        constexpr const std::u16string_view constToken_Path = u"path";
        constexpr const std::u16string_view constToken_Polygon = u"polygon";
        constexpr const std::u16string_view constToken_Polyline = u"polyline";
        constexpr const std::u16string_view constToken_Rect = u"rect";
        constexpr const std::u16string_view constToken_Image = u"image";

        constexpr const std::u16string_view constToken_LinearGradient = u"linearGradient";
        constexpr const std::u16string_view constTokenLowercase_LinearGradient = u"lineargradient";
        constexpr const std::u16string_view constToken_RadialGradient = u"radialGradient";
        constexpr const std::u16string_view constTokenLowercase_RadialGradient = u"radialgradient";
        constexpr const std::u16string_view constToken_Stop = u"stop";
        constexpr const std::u16string_view constToken_Offset = u"offset";
        constexpr const std::u16string_view constToken_X1 = u"x1";
        constexpr const std::u16string_view constToken_Y1 = u"y1";
        constexpr const std::u16string_view constToken_X2 = u"x2";
        constexpr const std::u16string_view constToken_Y2 = u"y2";
        constexpr const std::u16string_view constToken_Cx = u"cx";
        constexpr const std::u16string_view constToken_Cy = u"cy";
        constexpr const std::u16string_view constToken_Fx = u"fx";
        constexpr const std::u16string_view constToken_Fy = u"fy";
        constexpr const std::u16string_view constToken_R = u"r";
        constexpr const std::u16string_view constToken_GradientUnits = u"gradientUnits";
        constexpr const std::u16string_view constTokenLowercase_GradientUnits = u"gradientunits";
        constexpr const std::u16string_view constToken_GradientTransform = u"gradientTransform";
        constexpr const std::u16string_view constTokenLowercase_GradientTransform = u"gradienttransform";
        constexpr const std::u16string_view constToken_SpreadMethod = u"spreadMethod";
        constexpr const std::u16string_view constTokenLowercase_SpreadMethod = u"spreadmethod";
        constexpr const std::u16string_view constToken_Href = u"href";
        constexpr const std::u16string_view constToken_XlinkHref = u"xlink:href";
        constexpr const std::u16string_view constToken_StopColor = u"stop-color";
        constexpr const std::u16string_view constToken_StopOpacity = u"stop-opacity";

        constexpr const std::u16string_view constToken_Fill = u"fill";
        constexpr const std::u16string_view constToken_FillOpacity = u"fill-opacity";
        constexpr const std::u16string_view constToken_FillRule = u"fill-rule";

        constexpr const std::u16string_view constToken_Stroke = u"stroke";
        constexpr const std::u16string_view constToken_StrokeDasharray = u"stroke-dasharray";
        constexpr const std::u16string_view constToken_StrokeDashoffset = u"stroke-dashoffset";
        constexpr const std::u16string_view constToken_StrokeLinecap = u"stroke-linecap";
        constexpr const std::u16string_view constToken_StrokeLinejoin = u"stroke-linejoin";
        constexpr const std::u16string_view constToken_StrokeMiterlimit = u"stroke-miterlimit";
        constexpr const std::u16string_view constToken_StrokeOpacity = u"stroke-opacity";
        constexpr const std::u16string_view constToken_StrokeWidth = u"stroke-width";

        constexpr const std::u16string_view constToken_Text = u"text";
        constexpr const std::u16string_view constToken_BaselineShift = u"baseline-shift";

        constexpr const std::u16string_view constToken_FlowRoot = u"flowRoot";
        constexpr const std::u16string_view constTokenLowercase_FlowRoot = u"flowroot";

        static constexpr frozen::map<std::u16string_view, SVGToken, 133> aSVGTokenMapperList
        {
            { constToken_Width, SVGToken::Width },
            { constToken_Height, SVGToken::Height },
            { constToken_ViewBox, SVGToken::ViewBox },
            { constToken_Transform, SVGToken::Transform },
            { constToken_Style, SVGToken::Style },
            { constToken_Display, SVGToken::Display }, // #i121656#
            { constToken_D, SVGToken::D },
            { constToken_X, SVGToken::X },
            { constToken_Y, SVGToken::Y },
            { constToken_Xmlns, SVGToken::Xmlns },
            { constToken_Version, SVGToken::Version },
            { constToken_Id, SVGToken::Id },
            { constToken_Rx, SVGToken::Rx },
            { constToken_Ry, SVGToken::Ry },
            { constToken_Points, SVGToken::Points },
            { constToken_Dx, SVGToken::Dx },
            { constToken_Dy, SVGToken::Dy },
            { constToken_Rotate, SVGToken::Rotate },
            { constToken_TextLength, SVGToken::TextLength },
            { constToken_LengthAdjust, SVGToken::LengthAdjust },
            { constToken_Font, SVGToken::Font },
            { constToken_FontFamily, SVGToken::FontFamily },
            { constToken_FontSize, SVGToken::FontSize },
            { constToken_FontSizeAdjust, SVGToken::FontSizeAdjust },
            { constToken_FontStretch, SVGToken::FontStretch },
            { constToken_FontStyle, SVGToken::FontStyle },
            { constToken_FontVariant, SVGToken::FontVariant },
            { constToken_FontWeight, SVGToken::FontWeight },
            { constToken_Direction, SVGToken::Direction },
            { constToken_LetterSpacing, SVGToken::LetterSpacing },
            { constToken_TextDecoration, SVGToken::TextDecoration },
            { constToken_UnicodeBidi, SVGToken::UnicodeBidi },
            { constToken_WordSpacing, SVGToken::WordSpacing },
            { constToken_Tspan, SVGToken::Tspan },
            { constToken_Tref, SVGToken::Tref },
            { constToken_TextPath, SVGToken::TextPath },
            { constToken_StartOffset, SVGToken::StartOffset },
            { constToken_Method, SVGToken::Method },
            { constToken_Spacing, SVGToken::Spacing },
            { constToken_TextAlign, SVGToken::TextAlign },
            { constToken_PathLength, SVGToken::PathLength },
            { constToken_Type, SVGToken::Type },
            { constToken_Class, SVGToken::Class },
            { constToken_TextAnchor, SVGToken::TextAnchor },
            { constToken_XmlSpace, SVGToken::XmlSpace },
            { constToken_Color, SVGToken::Color },
            { constToken_ClipPathNode, SVGToken::ClipPathNode },
            { constToken_ClipPathProperty, SVGToken::ClipPathProperty },
            { constToken_Mask, SVGToken::Mask },
            { constToken_ClipPathUnits, SVGToken::ClipPathUnits },
            { constToken_MaskUnits, SVGToken::MaskUnits },
            { constToken_MaskContentUnits, SVGToken::MaskContentUnits },
            { constToken_ClipRule, SVGToken::ClipRule },
            { constToken_Marker, SVGToken::Marker },
            { constToken_MarkerStart, SVGToken::MarkerStart },
            { constToken_MarkerMid, SVGToken::MarkerMid },
            { constToken_MarkerEnd, SVGToken::MarkerEnd },
            { constToken_RefX, SVGToken::RefX },
            { constToken_RefY, SVGToken::RefY },
            { constToken_MarkerUnits, SVGToken::MarkerUnits },
            { constToken_MarkerWidth, SVGToken::MarkerWidth },
            { constToken_MarkerHeight, SVGToken::MarkerHeight },
            { constToken_Orient, SVGToken::Orient },
            { constToken_Pattern, SVGToken::Pattern },
            { constToken_PatternUnits, SVGToken::PatternUnits },
            { constToken_PatternContentUnits, SVGToken::PatternContentUnits },
            { constToken_PatternTransform, SVGToken::PatternTransform },
            { constToken_Opacity, SVGToken::Opacity },
            { constToken_Visibility, SVGToken::Visibility },
            { constToken_Title, SVGToken::Title },
            { constToken_Desc, SVGToken::Desc },

            { constToken_PreserveAspectRatio, SVGToken::PreserveAspectRatio },
            { constToken_Defer, SVGToken::Defer },
            { constToken_None, SVGToken::None },
            { constToken_XMinYMin, SVGToken::XMinYMin },
            { constToken_XMidYMin, SVGToken::XMidYMin },
            { constToken_XMaxYMin, SVGToken::XMaxYMin },
            { constToken_XMinYMid, SVGToken::XMinYMid },
            { constToken_XMidYMid, SVGToken::XMidYMid },
            { constToken_XMaxYMid, SVGToken::XMaxYMid },
            { constToken_XMinYMax, SVGToken::XMinYMax },
            { constToken_XMidYMax, SVGToken::XMidYMax },
            { constToken_XMaxYMax, SVGToken::XMaxYMax },
            { constToken_Meet, SVGToken::Meet },
            { constToken_Slice, SVGToken::Slice },

            { constToken_Defs, SVGToken::Defs },
            { constToken_G, SVGToken::G },
            { constToken_Svg, SVGToken::Svg },
            { constToken_Symbol, SVGToken::Symbol },
            { constToken_Use, SVGToken::Use },
            { constToken_A, SVGToken::A },

            { constToken_Circle, SVGToken::Circle },
            { constToken_Ellipse, SVGToken::Ellipse },
            { constToken_Line, SVGToken::Line },
            { constToken_Path, SVGToken::Path },
            { constToken_Polygon, SVGToken::Polygon },
            { constToken_Polyline, SVGToken::Polyline },
            { constToken_Rect, SVGToken::Rect },
            { constToken_Image, SVGToken::Image },

            { constToken_LinearGradient, SVGToken::LinearGradient },
            { constToken_RadialGradient, SVGToken::RadialGradient },
            { constToken_Stop, SVGToken::Stop },
            { constToken_Offset, SVGToken::Offset },
            { constToken_X1, SVGToken::X1 },
            { constToken_Y1, SVGToken::Y1 },
            { constToken_X2, SVGToken::X2 },
            { constToken_Y2, SVGToken::Y2 },
            { constToken_Cx, SVGToken::Cx },
            { constToken_Cy, SVGToken::Cy },
            { constToken_Fx, SVGToken::Fx },
            { constToken_Fy, SVGToken::Fy },
            { constToken_R, SVGToken::R },
            { constToken_GradientUnits, SVGToken::GradientUnits },
            { constToken_GradientTransform, SVGToken::GradientTransform },
            { constToken_SpreadMethod, SVGToken::SpreadMethod },
            { constToken_Href, SVGToken::Href },
            { constToken_XlinkHref, SVGToken::XlinkHref },
            { constToken_StopColor, SVGToken::StopColor },
            { constToken_StopOpacity, SVGToken::StopOpacity },

            { constToken_Fill, SVGToken::Fill },
            { constToken_FillOpacity, SVGToken::FillOpacity },
            { constToken_FillRule, SVGToken::FillRule },

            { constToken_Stroke, SVGToken::Stroke },
            { constToken_StrokeDasharray, SVGToken::StrokeDasharray },
            { constToken_StrokeDashoffset, SVGToken::StrokeDashoffset },
            { constToken_StrokeLinecap, SVGToken::StrokeLinecap },
            { constToken_StrokeLinejoin, SVGToken::StrokeLinejoin },
            { constToken_StrokeMiterlimit, SVGToken::StrokeMiterlimit },
            { constToken_StrokeOpacity, SVGToken::StrokeOpacity },
            { constToken_StrokeWidth, SVGToken::StrokeWidth },

            { constToken_Text, SVGToken::Text },
            { constToken_BaselineShift, SVGToken::BaselineShift },
            { constToken_FlowRoot, SVGToken::FlowRoot }
        };

        static constexpr frozen::map<std::u16string_view, SVGToken, 32> aLowerCaseList
        {
            { constTokenLowercase_ViewBox, SVGToken::ViewBox },
            { constTokenLowercase_TextLength, SVGToken::TextLength },
            { constTokenLowercase_LengthAdjust, SVGToken::LengthAdjust },
            { constTokenLowercase_TextPath, SVGToken::TextPath },
            { constTokenLowercase_StartOffset, SVGToken::StartOffset },
            { constTokenLowercase_PathLength, SVGToken::PathLength },
            { constTokenLowercase_ClipPathNode, SVGToken::ClipPathNode },
            { constTokenLowercase_ClipPathUnits, SVGToken::ClipPathUnits },
            { constTokenLowercase_MaskUnits, SVGToken::MaskUnits },
            { constTokenLowercase_MaskContentUnits, SVGToken::MaskContentUnits },
            { constTokenLowercase_MarkerUnits, SVGToken::MarkerUnits },
            { constTokenLowercase_MarkerWidth, SVGToken::MarkerWidth },
            { constTokenLowercase_MarkerHeight, SVGToken::MarkerHeight },
            { constTokenLowercase_PatternUnits, SVGToken::PatternUnits },
            { constTokenLowercase_PatternContentUnits, SVGToken::PatternContentUnits },
            { constTokenLowercase_PatternTransform, SVGToken::PatternTransform },
            { constTokenLowercase_PreserveAspectRatio, SVGToken::PreserveAspectRatio },
            { constTokenLowercase_XMinYMin, SVGToken::XMinYMin },
            { constTokenLowercase_XMidYMin, SVGToken::XMidYMin },
            { constTokenLowercase_XMaxYMin, SVGToken::XMaxYMin },
            { constTokenLowercase_XMinYMid, SVGToken::XMinYMid },
            { constTokenLowercase_XMidYMid, SVGToken::XMidYMid },
            { constTokenLowercase_XMaxYMid, SVGToken::XMaxYMid },
            { constTokenLowercase_XMinYMax, SVGToken::XMinYMax },
            { constTokenLowercase_XMidYMax, SVGToken::XMidYMax },
            { constTokenLowercase_XMaxYMax, SVGToken::XMaxYMax },
            { constTokenLowercase_LinearGradient, SVGToken::LinearGradient },
            { constTokenLowercase_RadialGradient, SVGToken::RadialGradient },
            { constTokenLowercase_GradientUnits, SVGToken::GradientUnits },
            { constTokenLowercase_GradientTransform, SVGToken::GradientTransform },
            { constTokenLowercase_SpreadMethod, SVGToken::SpreadMethod },
            { constTokenLowercase_FlowRoot, SVGToken::FlowRoot }
        };

        SVGToken StrToSVGToken(const OUString& rStr, bool bCaseIndependent)
        {
            OUString aSearchString = rStr.startsWith("svg:") ? rStr.copy(4) : rStr;

            auto const aResult = aSVGTokenMapperList.find(aSearchString);

            if (aResult == aSVGTokenMapperList.end())
            {
                if (bCaseIndependent)
                {
                    auto const aResultLowerCase(aLowerCaseList.find(rStr.toAsciiLowerCase()));

                    if (aResultLowerCase == aLowerCaseList.end())
                    {
                        return SVGToken::Unknown;
                    }
                    else
                    {
                        return aResultLowerCase->second;
                    }
                }

                return SVGToken::Unknown;
            }
            else
            {
                return aResult->second;
            }
        }

        OUString getStrTitle()
        {
            return OUString(constToken_Title);
        }

        OUString getStrDesc()
        {
            return OUString(constToken_Desc);
        }
} // end of namespace svgio

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
