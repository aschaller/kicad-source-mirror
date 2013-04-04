/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2013 CERN
 * @author Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
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

/**
 * @file class_drawpanel_gal.h:
 * @brief EDA_DRAW_PANEL_GAL class definition.
 */

#ifndef  PANELGAL_WXSTRUCT_H
#define  PANELGAL_WXSTRUCT_H

#include <wx/wx.h>
#include <wx/window.h>

#include <math/vector2d.h>

class BOARD;

namespace KiGfx
{
class GAL;
class VIEW;
class WX_VIEW_CONTROLS;
class PAINTER;
};


class EDA_DRAW_PANEL_GAL : public wxWindow
{
public:
    enum GalType {
        GAL_TYPE_OPENGL,    ///< OpenGL implementation
        GAL_TYPE_CAIRO,     ///< Cairo implementation
        GAL_TYPE_WXDC       ///< WXDC implementation
    };

    EDA_DRAW_PANEL_GAL( wxWindow* aParentWindow, wxWindowID aWindowId, const wxPoint& aPosition,
                        const wxSize& aSize, GalType aGalType = GAL_TYPE_OPENGL );
    ~EDA_DRAW_PANEL_GAL();

    /**
     * Function SwitchBackend
     * Switches method of rendering graphics.
     * @param aGalType is a type of rendering engine that you want to use.
     */
    void SwitchBackend( GalType aGalType, bool aUseShaders = false );

    /**
     * Function GetGAL
     * Returns a pointer to the GAL instance used in the panel.
     * @return KiGfx::GAL* Instance of GAL.
     */
    KiGfx::GAL* GetGAL() { return m_gal; }

    void SetView( KiGfx::VIEW* aView ) { m_view = aView; }
    KiGfx::VIEW* GetView() const { return m_view; }

protected:
    void onPaint( wxEvent& event );
    void onSize( wxSizeEvent& aEvent );
    void onMotion( wxMouseEvent& event );
    void onButton( wxMouseEvent& event );
    void onEraseBackground( wxEvent& event );

    KiGfx::GAL*              m_gal;              ///< Interface for drawing objects on a 2D-surface
    KiGfx::VIEW*             m_view;             ///< Stores view settings (scale, center, etc.)
                                                 ///< and items to be drawn
    KiGfx::PAINTER*          m_painter;          ///< Contains information about how to draw items
                                                 ///< using GAL
    KiGfx::WX_VIEW_CONTROLS* m_viewControls;     ///< Control for VIEW (moving, zooming, etc.)

    VECTOR2D                 m_screenSize;       ///< Stores current screen size
    wxWindow*                m_parentFrame;      ///< Pointer to the parent frame

    std::string m_galShaderPath;            ///< Path to shader files, used in OpenGL mode
};

#endif