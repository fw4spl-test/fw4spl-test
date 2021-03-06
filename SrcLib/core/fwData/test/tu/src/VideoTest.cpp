/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fwData/Video.hpp>
#include "VideoTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( ::fwData::ut::VideoTest );

namespace fwData
{
namespace ut
{

void VideoTest::setUp()
{
    // Set up context before running a test.
}

//------------------------------------------------------------------------------

void VideoTest::tearDown()
{
    // Clean up after the test run.
}

//------------------------------------------------------------------------------

void VideoTest::methode1()
{
    ::boost::uint32_t VALUE   = 0 ;
    ::boost::uint8_t VALUE1   = 1 ;

    // process
    ::fwData::Video::sptr video = ::fwData::Video::New();

    // check
    CPPUNIT_ASSERT_EQUAL(video->getXSize(), VALUE);
    CPPUNIT_ASSERT_EQUAL(video->getYSize(), VALUE);
    CPPUNIT_ASSERT_EQUAL(video->getBPP(),  VALUE1);
}

} //namespace ut
} //namespace fwData

