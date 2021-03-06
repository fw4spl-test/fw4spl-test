/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _IO_IREADER_HPP_
#define _IO_IREADER_HPP_

#include <boost/filesystem/path.hpp>

#include <fwServices/IService.hpp>

#include "io/config.hpp"
#include "io/ioTypes.hpp"

namespace io
{

/**
 * @brief Reader service API. It manages extension points definition and extension configuration
 * @class   IReader
 *
 * This class represents the base interface for reader services.
 * Use the base service methods :
 * @li The service is configured with methods setConfiguration(cfg) and configure()
 * @li The method start() initialize the service
 * @li To read the object use update() method
 * @li Finally we must call stop() before deleting the service
 * @todo ACH : remove some methods : getSupportedExtensions ? getSelectorDialogTitle ?
 */
class IO_CLASS_API IReader : public fwServices::IService
{

public :
    fwCoreServiceClassDefinitionsMacro ( (IReader)(::fwServices::IService) ) ;

    /**
     * @name    Specific service methods for reading
     */
    //@{

    /**
     * @brief Configure the image path (by default does nothing).
     *
     * This method is used to find
     * the file path  using a file selector.
     */
    IO_API virtual void configureWithIHM() = 0;

    /**
     * @brief   returns  (filename) extension
     */
    IO_API virtual std::vector< std::string > getSupportedExtensions() ;

    /**
     * @brief   returns  the title of selector dialog box
     */
    IO_API virtual std::string getSelectorDialogTitle();

    /**
     * @brief This method must be implemented by concrete service readers
     * that use path file system to read data.
     *
     * This method returns supported path format (file, files or folder).
     * A reader can support file and folder, or files and folder, but not
     * file and files ( because files include file concept ).
     */
    IO_API virtual ::io::IOPathType getIOPathType() const;

    /**
     * @brief Returns the file path setted by user or setted during service configuration
     * @pre exception if a file path is not defined  ( m_locations.empty() )
     * @pre exception if service not supported FILE management
     */
    IO_API const ::boost::filesystem::path &getFile() const;

    /**
     * @brief Sets file path
     * @pre exception if service not supported FILE management
     */
    IO_API void setFile(const ::boost::filesystem::path &file);

    /**
     * @brief Returns file paths setted by user or setted during service configuration
     * @pre exception if a file path is not defined ( m_locations.empty() )
     * @pre exception if service not supported FILES management
     */
    IO_API const ::io::LocationsType &getFiles() const;

    /**
     * @brief Sets file paths
     * @pre exception if service not supported FILES management
     */
    IO_API void setFiles(const ::io::LocationsType &files);

    /**
     * @brief Returns folder path setted by user or setted during service configuration
     * @pre exception if a folder path is not defined ( m_locations.empty() )
     * @pre exception if service not supported FOLDER management
     */
    IO_API const ::boost::filesystem::path &getFolder() const;

    /**
     * @brief Clear any location set by the setFile/setFiles/setFolder setter
     */
    IO_API void clearLocations();

    /**
     * @brief Returns file/files/folder paths setted by user or setted during service configuration
     * @pre exception if a file path is not defined ( m_locations.empty() )
     */
    IO_API const ::io::LocationsType & getLocations() const;

    /**
     * @brief Sets folder path
     * @pre exception if service not supported FOLDER management
     */
    IO_API void setFolder(const ::boost::filesystem::path &folder);

    /// Returns if a location has been defined ( by the configuration process or directly by user )
    IO_API bool hasLocationDefined() const;

    //@}

protected:

    IO_API IReader() throw() ;

    IO_API virtual ~IReader() throw() ;

    /**
     * @brief This method proposes to parse xml configuration to retrieve
     * file/files/folder paths.
     *
     * You can implement your configuring method if you wan check another
     * information or information not correspond to a path on filesystem,
     * else you must use this generic approach.
     *
     * Sample configuration for a file:
     * @verbatim
     <service ... >
        <file>/home/user/myFile.jpg</file>
     </service>
     @endverbatim
     * Sample configuration for many files:
     * @verbatim
     <service ... >
        <file>/home/user/myFile01.jpg</file>
        <file>/home/user/myFile02.jpg</file>
        <file>/home/user/myFile03.jpg</file>
     </service>
     @endverbatim
     * Sample configuration for a folder:
     * @verbatim
     <service ... >
        <folder>/home/user/myFolder</folder>
     </service>
     @endverbatim
     */
    IO_API virtual void configuring() throw (fwTools::Failed);


private:

    /// Value to stock file or folder paths
    ::io::LocationsType m_locations;
};

}


#endif /*_IO_IREADER_HPP_*/
