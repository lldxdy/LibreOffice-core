/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <basegfx/units/LengthUnitBase.hxx>
#include <basegfx/range/Range2D.hxx>
#include <basegfx/tuple/Size2D.hxx>
#include <basegfx/range/b2drange.hxx>

#include <tools/gen.hxx>

namespace gfx
{
typedef LengthUnitBase<sal_Int64> Length;

struct LengthTraits
{
    static constexpr Length minVal() { return Length::min(); };
    static constexpr Length maxVal() { return Length::max(); };
    static constexpr Length neutral() { return Length(); };

    typedef Length DifferenceType;
};

typedef basegfx::Range2D<gfx::Length, gfx::LengthTraits> Range2DL;
typedef basegfx::Tuple2D<gfx::Length> Tuple2DL;
typedef basegfx::Size2D<gfx::Length> Size2DL;

namespace length
{
static inline Size2DL fromSizeHmm(Size const& rSize)
{
    auto width = Length::hmm(rSize.getWidth());
    auto height = Length::hmm(rSize.getHeight());
    return Size2DL(width, height);
}

static inline Size toSizeHmm(Size2DL const& rTuple)
{
    auto width = rTuple.getWidth().as_hmm();
    auto height = rTuple.getHeight().as_hmm();
    return Size(width, height);
}

static inline Range2DL fromRectangleHmm(tools::Rectangle const& rRectangle)
{
    auto left = Length::hmm(rRectangle.Left());
    auto top = Length::hmm(rRectangle.Top());
    auto right = Length::hmm(rRectangle.Right());
    auto bottom = Length::hmm(rRectangle.Bottom());
    return Range2DL(left, top, right, bottom);
}

static inline basegfx::B2DRange toB2DRange2DHmm(Range2DL const& rRange2D)
{
    auto left = rRange2D.getMinX().as_hmm();
    auto top = rRange2D.getMinY().as_hmm();
    auto right = rRange2D.getMaxX().as_hmm();
    auto bottom = rRange2D.getMaxY().as_hmm();
    return basegfx::B2DRange(left, top, right, bottom);
}

static inline tools::Rectangle toRectangleHmm(Range2DL const& rRange2D)
{
    auto left = rRange2D.getMinX().as_hmm();
    auto top = rRange2D.getMinY().as_hmm();
    auto right = rRange2D.getMaxX().as_hmm();
    auto bottom = rRange2D.getMaxY().as_hmm();
    return tools::Rectangle(left, top, right, bottom);
}

} // end namespace length

} // end namespace gfx

constexpr gfx::Length operator"" _emu(unsigned long long value) { return gfx::Length::emu(value); }
constexpr gfx::Length operator"" _in(unsigned long long value) { return gfx::Length::in(value); }
constexpr gfx::Length operator"" _cm(unsigned long long value) { return gfx::Length::cm(value); }
constexpr gfx::Length operator"" _mm(unsigned long long value) { return gfx::Length::mm(value); }
constexpr gfx::Length operator"" _hmm(unsigned long long value) { return gfx::Length::hmm(value); }
constexpr gfx::Length operator"" _twip(unsigned long long value)
{
    return gfx::Length::twip(value);
}
constexpr gfx::Length operator"" _pt(unsigned long long value) { return gfx::Length::pt(value); }
constexpr gfx::Length operator"" _px(unsigned long long value) { return gfx::Length::px(value); }

constexpr gfx::Length operator"" _in(long double value)
{
    return gfx::Length::emu(std::round(gfx::constFactor_in_to_EMU * value));
}
constexpr gfx::Length operator"" _cm(long double value)
{
    return gfx::Length::emu(std::round(gfx::constFactor_cm_to_EMU * value));
}

constexpr gfx::Length operator"" _mm(long double value)
{
    return gfx::Length::emu(std::round(gfx::constFactor_mm_to_EMU * value));
}

constexpr gfx::Length operator"" _hmm(long double value)
{
    return gfx::Length::emu(std::round(gfx::constFactor_hmm_to_EMU * value));
}

constexpr gfx::Length operator"" _twip(long double value)
{
    return gfx::Length::emu(std::round(gfx::constFactor_twip_to_EMU * value));
}

constexpr gfx::Length operator"" _pt(long double value)
{
    return gfx::Length::emu(std::round(gfx::constFactor_pt_to_EMU * value));
}

constexpr gfx::Length operator"" _px(long double value)
{
    return gfx::Length::emu(std::round(gfx::constFactor_px_to_EMU * value));
}

/** Write to char stream */
template <typename charT, typename traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& stream,
                                                     const gfx::Length& rLength)
{
    return stream << rLength.raw() << " (twip=" << rLength.as_twip() << ", hmm=" << rLength.as_hmm()
                  << ")";
}
