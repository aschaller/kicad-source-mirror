/*
 * This program source code file is part of KICAD, a free EDA CAD application.
 *
 * Copyright (C) 2012 Torsten Hueter, torstenhtr <at> gmx.de
 * Copyright (C) 2012 Kicad Developers, see change_log.txt for contributors.
 *
 * Color class
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef COLOR4D_H_
#define COLOR4D_H_

#include <colors.h>

namespace KiGfx
{
/**
 * Class COLOR4D
 * is the color representation with 4 components: red, green, blue, alpha.
 */
class COLOR4D
{
public:
    // Constructor (creates the Color 0,0,0,0)
    COLOR4D() :
        r( 0 ), g( 0 ), b( 0 ), a( 1 )
    {
    }

    /**
     * @brief Constructor
     *
     * @param aRed   is the red component   [0.0 .. 1.0].
     * @param aGreen is the green component [0.0 .. 1.0].
     * @param aBlue  is the blue component  [0.0 .. 1.0].
     * @param aAlpha is the alpha value     [0.0 .. 1.0].
     */
    COLOR4D( double aRed, double aGreen, double aBlue, double aAlpha ) :
        r( aRed ), g( aGreen ), b( aBlue ), a( aAlpha )
    {
    }

    /**
     * @brief Constructor
     *
     * @param aColor is one of KiCad's palette colors.
     * @see EDA_COLOR_T
     */
    COLOR4D( EDA_COLOR_T aColor );

    /**
     * Function Highlight
     * Makes the color brighter by a given factor.
     * @param aFactor Specifies how bright the color should become (valid values: 0.0 .. 1.0).
     * @return COLOR4D& Brightened color.
     */
    COLOR4D& Highlight( double aFactor )
    {
        r = (double) r * (1.0 - aFactor) + aFactor;
        g = (double) g * (1.0 - aFactor) + aFactor;
        b = (double) b * (1.0 - aFactor) + aFactor;

        return *this;
    }

    /**
     * Function Darken
     * Makes the color darker by a given factor.
     * @param aFactor Specifies how dark the color should become (valid values: 0.0 .. 1.0).
     * @return COLOR4D& Darkened color.
     */
    COLOR4D& Darken( double aFactor )
    {
        r = (double) r * (1.0 - aFactor);
        g = (double) g * (1.0 - aFactor);
        b = (double) b * (1.0 - aFactor);

        return *this;
    }

    /**
     * Function Highlighted
     * Returns a color that is brighter by a given factor, without modifying object.
     * @param aFactor Specifies how bright the color should become (valid values: 0.0 .. 1.0).
     * @return COLOR4D Highlightedd color.
     */
    COLOR4D Highlighted( double aFactor ) const
    {
        return COLOR4D( r * (1.0 - aFactor) + aFactor,
                        g * (1.0 - aFactor) + aFactor,
                        b * (1.0 - aFactor) + aFactor,
                        a );
    }

    /**
     * Function Darkened
     * Returns a color that is darker by a given factor, without modifying object.
     * @param aFactor Specifies how dark the color should become (valid values: 0.0 .. 1.0).
     * @return COLOR4D Darkened color.
     */
    COLOR4D Darkened( double aFactor ) const
    {
        return COLOR4D( r * (1.0 - aFactor),
                        g * (1.0 - aFactor),
                        b * (1.0 - aFactor),
                        a );
    }

    /// @brief Equality operator, are two colors equal
    const bool operator==( const COLOR4D& aColor );

    /// @brief Not equality operator, are two colors not equal
    const bool operator!=( const COLOR4D& aColor );

    // Color components: red, green, blue, alpha
    double r; ///< Red component
    double g; ///< Green component
    double b; ///< Blue component
    double a; ///< Alpha component
};
} // namespace KiGfx

#endif /* COLOR4D_H_ */