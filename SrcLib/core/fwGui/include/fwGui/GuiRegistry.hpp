/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWGUI_GUIREGISTRY_HPP_
#define _FWGUI_GUIREGISTRY_HPP_


#include "fwGui/GuiBaseObject.hpp"
#include "fwGui/config.hpp"
#include "fwGui/container/fwContainer.hpp"
#include "fwGui/container/fwMenuBar.hpp"
#include "fwGui/container/fwToolBar.hpp"
#include "fwGui/container/fwMenu.hpp"
#include "fwGui/container/fwMenuItem.hpp"

namespace fwGui
{

/**
 * @brief   This class contains helpers to manage all fwContainer in the application.
 * @class   GuiRegistry
 * 
 * @date    2009-2010.
 *
 */
class FWGUI_CLASS_API GuiRegistry : public ::fwGui::GuiBaseObject
{

public :

    typedef std::map< std::string , ::fwGui::container::fwContainer::sptr > ContainerMapType;
    typedef std::map< std::string , ::fwGui::container::fwMenuBar::sptr >   MenuBarMapType;
    typedef std::map< std::string , ::fwGui::container::fwToolBar::sptr >   ToolBarMapType;
    typedef std::map< std::string , ::fwGui::container::fwMenu::sptr >      MenuMapType;
    typedef std::vector< std::string >                           ParentSidsType;
    typedef std::map< std::string , ParentSidsType > ActionToParentMapType;

    fwCoreNonInstanciableClassDefinitionsMacro( (GuiRegistry)(::fwGui::GuiBaseObject) )

    /**
     * @brief   Constructor.
     */
    FWGUI_API GuiRegistry() ;

    /**
     * @brief   Destructor. Do nothing.
     */
    FWGUI_API virtual ~GuiRegistry() ;

    //-----------------------------------------------------------------------------

    /**
     * @name    Helper SID-container methods
     */
    ///@{

    /**
     * @brief Registers container associate with service ID.
     */
    FWGUI_API static void registerSIDContainer(std::string sid, ::fwGui::container::fwContainer::sptr container);

    /**
     * @brief Unregisters container associate with service ID.
     */
    FWGUI_API static void unregisterSIDContainer(std::string sid);

    /**
     * @brief Returns fwContainer associate with service ID.
     */
    FWGUI_API static ::fwGui::container::fwContainer::sptr getSIDContainer(std::string sid);

    ///@}

    //-----------------------------------------------------------------------------

    /**
     * @name    Helper WID-container methods
     */
    ///@{

    /**
     * @brief Registers container associate with window ID.
     */
    FWGUI_API static void registerWIDContainer(std::string wid, ::fwGui::container::fwContainer::sptr container);

    /**
     * @brief Unregisters container associate with window ID.
     */
    FWGUI_API static void unregisterWIDContainer(std::string wid);

    /**
     * @brief Returns fwContainer associate with window ID.
     */
    FWGUI_API static ::fwGui::container::fwContainer::sptr getWIDContainer(std::string wid);

    ///@}

    //-----------------------------------------------------------------------------

    /**
     * @name    Helper SID-MenuBar methods
     */
    ///@{

    /**
     * @brief Registers fwMenuBar associate with service ID.
     */
    FWGUI_API static void registerSIDMenuBar(std::string sid, ::fwGui::container::fwMenuBar::sptr menuBar);

    /**
     * @brief Unregisters fwMenuBar associate with service ID.
     */
    FWGUI_API static void unregisterSIDMenuBar(std::string sid);
    /**
     * @brief Returns fwMenuBar associate with service ID.
     */
    FWGUI_API static ::fwGui::container::fwMenuBar::sptr getSIDMenuBar(std::string sid);
    ///@}


    //-----------------------------------------------------------------------------

    /**
     * @name    Helper SID-ToolBar methods
     */
    ///@{

    /**
     * @brief Registers fwToolBar associate with service ID.
     */
    FWGUI_API static void registerSIDToolBar(std::string sid, ::fwGui::container::fwToolBar::sptr toolBar);

    /**
     * @brief Unregisters fwToolBar associate with service ID.
     */
    FWGUI_API static void unregisterSIDToolBar(std::string sid);
    /**
     * @brief Returns fwToolBar associate with service ID.
     */
    FWGUI_API static ::fwGui::container::fwToolBar::sptr getSIDToolBar(std::string sid);
    ///@}

    //-----------------------------------------------------------------------------

    /**
     * @name    Helper SID-Menu methods
     */
    ///@{

    /**
     * @brief Registers fwMenu associate with service ID.
     */
    FWGUI_API static void registerSIDMenu(std::string sid, ::fwGui::container::fwMenu::sptr menu);

    /**
     * @brief Unregisters fwMenu associate with service ID.
     */
    FWGUI_API static void unregisterSIDMenu(std::string sid);
    /**
     * @brief Returns fwMenu associate with service ID.
     */
    FWGUI_API static ::fwGui::container::fwMenu::sptr getSIDMenu(std::string sid);
    ///@}

    //-----------------------------------------------------------------------------

    /**
     * @name    Helper Action-Menu methods
     */
    ///@{

    /**
     * @brief Registers action sid associted with a parent sid.
     */
    FWGUI_API static void registerActionSIDToParentSID(std::string actionSid, std::string parentSid);

    /**
     * @brief Unregisters action sid associted with a parent sid.
     */
    FWGUI_API static void unregisterActionSIDToParentSID(std::string actionSid, std::string parentSid);

    /**
     * @brief Method called when the action service is stopping.
     * Call parent service actionServiceStopping() method
     */
    FWGUI_API static void actionServiceStopping(std::string actionSid);

    /**
     * @brief Method called when the action service is starting.
     * Call parent service actionServiceStarting() method
     */
    FWGUI_API static void actionServiceStarting(std::string actionSid);

    /**
     * @brief Method called when the action service is activated or not.
     * Call parent service actionServiceSetActive() method
     */
    FWGUI_API static void actionServiceSetActive(std::string actionSid, bool isActive);

    /**
     * @brief Method called when the action service is executable or not.
     * Call parent service actionServiceSetExecutable() method
     */
    FWGUI_API static void actionServiceSetExecutable(std::string actionSid, bool isExecutable);
    ///@}

protected :

    static ContainerMapType       m_globalSIDToFwContainer;
    static ContainerMapType       m_globalWIDToFwContainer;
    static MenuBarMapType         m_globalSIDToFwMenuBar;
    static ToolBarMapType         m_globalSIDToFwToolBar;
    static MenuMapType            m_globalSIDToFwMenu;

    /// Parent sid can be Menu sid or ToolBar sid
    static ActionToParentMapType  m_actionSIDToParentSID;

};

} // namespace fwGui

#endif /*_FWGUI_GUIREGISTRY_HPP_*/


