/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWDATA_COMPOSITE_HPP__
#define __FWDATA_COMPOSITE_HPP__

#include <map>

#include <boost/shared_ptr.hpp>

#include "fwData/config.hpp"

#include "fwData/Object.hpp"
#include "fwData/factory/new.hpp"


// boost 1.47 issue with FOREACH
#include <boost/version.hpp>
#if BOOST_VERSION >= 104700
#include <boost/foreach.hpp>

namespace fwData
{ class Composite; }

inline boost::mpl::true_ * boost_foreach_is_noncopyable( ::fwData::Composite *&, BOOST_FOREACH_TAG_DEFAULT )
{ return 0; }

#endif //BOOST_VERSION >= 104700



fwCampAutoDeclareDataMacro((fwData)(Composite), FWDATA_API);


namespace fwData
{

/**
 * @brief This class defines a composite object.
 *
 * Composite contains a map of ::fwData::Object.
 */

class FWDATA_CLASS_API Composite : public Object
{
public:
    fwCoreClassDefinitionsWithFactoryMacro( (Composite)(::fwData::Object), (()), ::fwData::factory::New< Composite >);
    fwCampMakeFriendDataMacro((fwData)(Composite));

    typedef std::map< std::string, ::fwData::Object::sptr > ContainerType;

    typedef ContainerType::key_type KeyType;
    typedef ContainerType::mapped_type MappedType;
    typedef ContainerType::value_type ValueType;
    typedef ContainerType::iterator IteratorType;
    typedef ContainerType::const_iterator ConstIteratorType;
    typedef ContainerType::reverse_iterator ReverseIteratorType;
    typedef ContainerType::const_reverse_iterator ConstReverseIteratorType;
    typedef ContainerType::size_type SizeType;

    /// boost_foreach/stl compatibility
    /// @{
    typedef ContainerType::key_type key_type;
    typedef ContainerType::mapped_type mapped_type;
    typedef ContainerType::value_type value_type;
    typedef ContainerType::iterator iterator;
    typedef ContainerType::const_iterator const_iterator;
    typedef ContainerType::reverse_iterator reverse_iterator;
    typedef ContainerType::const_reverse_iterator const_reverse_iterator;
    typedef ContainerType::size_type size_type;


    /**
     * @brief Constructor
     * @param key Private construction key
     */
    FWDATA_API Composite( ::fwData::Object::Key key );

    /// Destructor
    FWDATA_API virtual ~Composite();


    IteratorType begin() { return m_attrContainer.begin(); }
    IteratorType end()   { return m_attrContainer.end(); }
    ConstIteratorType begin() const { return m_attrContainer.begin(); }
    ConstIteratorType end()   const { return m_attrContainer.end(); }

    ReverseIteratorType rbegin() { return m_attrContainer.rbegin(); }
    ReverseIteratorType rend()   { return m_attrContainer.rend(); }
    ConstReverseIteratorType rbegin() const { return m_attrContainer.rbegin(); }
    ConstReverseIteratorType rend()   const { return m_attrContainer.rend(); }

    bool empty() const { return m_attrContainer.empty(); }
    SizeType size() const { return m_attrContainer.size(); }

    mapped_type& operator[] ( KeyType n )
    {return this->m_attrContainer[n]; }

    IteratorType find ( const KeyType& x ) { return m_attrContainer.find(x); }
    ConstIteratorType find ( const KeyType& x ) const { return m_attrContainer.find(x); }

    SizeType count ( const KeyType& x ) const { return m_attrContainer.count(x); }
    /// @}



    /// @brief get/set the map of std::string/::fwData::Object
    /// @{
    ContainerType &getContainer(){ return m_attrContainer; }
    fwDataGetSetCRefMacro(Container, ContainerType);
    /// @}


    /// Defines shallow copy
    FWDATA_API void shallowCopy( const Object::csptr& _source );

    /// Defines deep copy
    FWDATA_API void cachedDeepCopy(const Object::csptr& _source, DeepCopyCacheType &cache);

    /// Method to initialize a ::fwData::Composite from a std::map< string, X >
    template< class DATATYPE >
    void setDataContainer( const std::map< std::string, SPTR(DATATYPE) > & map )
    {
        this->getContainer().clear();
        this->getContainer().insert( map.begin(), map.end() );
    }

    /// Method to get a std::map< string, X > from ::fwData::Composite
    template< class DATATYPE >
    std::map< std::string, SPTR(DATATYPE) > getDataContainer() const
    {
        std::map< std::string, SPTR(DATATYPE) > map;
        SPTR(DATATYPE) castData;
        BOOST_FOREACH( ::fwData::Composite::value_type elem, *this )
        {
            castData = ::boost::dynamic_pointer_cast<DATATYPE>( elem.second );
            OSLM_ASSERT("DynamicCast "<< ::fwCore::TypeDemangler<DATATYPE>().getFullClassname()<<" failed", castData);
            map[elem.first] = castData;
        }

        return map;
    }

    /**
     * @brief Returns object in composite associated with the key.
     *  If no such object exists, a null object is returned.
     *
     *  @param key the key of the object to find
     *
     *  @return requested object in composite associated with the key
     */
    template< class DATATYPE >
    SPTR(DATATYPE) at(const std::string& key)
    {
        SPTR(DATATYPE) castData;
        ::fwData::Composite::iterator iter = this->find(key);
        if(iter != this->end())
        {
            castData = ::boost::dynamic_pointer_cast<DATATYPE>(iter->second);
            SLM_TRACE_IF("DynamicCast "+ ::fwCore::TypeDemangler<DATATYPE>().getFullClassname()+" failed", !castData);
        }
        else
        {
            SLM_TRACE( "Object '" + key + "' not found.");
        }
        return castData;
    }

    /**
     * @brief Returns object in composite associated with the key.
     *  If no such object exists, a null object is returned.
     *
     *  @param key the key of the object to find
     *
     *  @return requested object in composite associated with the key
     */
    template< class DATATYPE >
    CSPTR(DATATYPE) at(const std::string& key) const
    {
        CSPTR(DATATYPE) castData;
        ::fwData::Composite::const_iterator iter = this->find(key);
        if(iter != this->end())
        {
            castData = ::boost::dynamic_pointer_cast<DATATYPE>(iter->second);
            SLM_TRACE_IF("DynamicCast "+ ::fwCore::TypeDemangler<DATATYPE>().getFullClassname()+" failed", !castData);
        }
        else
        {
            SLM_TRACE( "Object '" + key + "' not found.");
        }
        return castData;
    }
protected:
    ContainerType m_attrContainer;
};

} //namespace fwData

#endif /* __FWDATA_COMPOSITE_HPP__ */

