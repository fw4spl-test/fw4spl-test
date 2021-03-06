/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <iostream>
#include <exception>
#include <vector>
#include <ostream>
#include <map>

#include <fwData/Graph.hpp>
#include <fwData/Node.hpp>
#include <fwData/Edge.hpp>
#include <fwData/Port.hpp>
#include "GraphTest.hpp"



// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ::fwData::ut::GraphTest );

namespace fwData
{
namespace ut
{

//------------------------------------------------------------------------------

void GraphTest::setUp()
{
    // Set up context before running a test.
}

//------------------------------------------------------------------------------

void GraphTest::tearDown()
{
    // Clean up after the test run.
}

//------------------------------------------------------------------------------

void GraphTest::normalCase()
{
    // G :
    // n1 --e--> n2
    ::fwData::Graph::sptr g( ::fwData::Graph::New() );

    ::fwData::Node::sptr n1( ::fwData::Node::New() );
    ::fwData::Port::sptr p1( ::fwData::Port::New() );
    p1->setIdentifier("sizex");
    p1->setType("float");
    n1->addOutputPort( p1 );

    ::fwData::Node::sptr n2( ::fwData::Node::New() );
    ::fwData::Port::sptr p2( ::fwData::Port::New() );
    p2->setIdentifier("threshold");
    p2->setType("float");
    n2->addInputPort( p2 );

    ::fwData::Edge::sptr e( ::fwData::Edge::New() );
    e->setIdentifiers("sizex","threshold");

    g->addNode(n1);
    g->addNode(n2);
    g->addEdge(e,n1,n2);

    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getInputEdges(n1).size() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getOutputEdges(n1).size() );
    CPPUNIT_ASSERT_EQUAL( e, g->getOutputEdges(n1).at(0) );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getInputEdges(n2).size() );
    CPPUNIT_ASSERT_EQUAL( e, g->getInputEdges(n2).at(0) );
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getOutputEdges(n2).size() );

    CPPUNIT_ASSERT_EQUAL( n1, g->getSourceNode(e) );
    CPPUNIT_ASSERT_EQUAL( n2, g->getDestinationNode(e) );

    // Remove to obtain empty graph
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );
    g->removeEdge(e);
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbEdges() );
    g->removeNode(n1);
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbEdges() );
    g->removeNode(n2);
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbEdges() );
}

//------------------------------------------------------------------------------

void GraphTest::limitCase1()
{
    // G :
    // n1 --e1--> n2
    ::fwData::Graph::sptr g( ::fwData::Graph::New() );

    ::fwData::Node::sptr n1( ::fwData::Node::New() );
    ::fwData::Port::sptr p1( ::fwData::Port::New() );
    p1->setIdentifier("sizex");
    p1->setType("float");
    n1->addOutputPort( p1 );

    ::fwData::Node::sptr n2( ::fwData::Node::New() );
    ::fwData::Port::sptr p2( ::fwData::Port::New() );
    p2->setIdentifier("threshold");
    p2->setType("float");
    n2->addInputPort( p2 );

    ::fwData::Edge::sptr e1( ::fwData::Edge::New() );
    e1->setIdentifiers("sizex","threshold");

    bool success;

    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbEdges() );

    success = g->addNode(n1);
    CPPUNIT_ASSERT_EQUAL( success ,  true );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbEdges() );

    success = g->addNode(n1);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbEdges() );

    success = g->addNode(n2);
    CPPUNIT_ASSERT_EQUAL( success ,  true );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)0, g->getNbEdges() );


    success = g->addEdge(e1,n1,n2);
    CPPUNIT_ASSERT_EQUAL( success ,  true );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    success = g->addEdge(e1,n1,n2);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    ::fwData::Node::sptr n3( ::fwData::Node::New() );
    ::fwData::Port::sptr p3( ::fwData::Port::New() );
    p3->setIdentifier("sizex");
    p3->setType("float");
    n3->addOutputPort( p3 );

    success = g->addEdge(e1,n3,n2);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    success = g->addEdge(e1,n1,n3);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    ::fwData::Edge::sptr e2( ::fwData::Edge::New() );
    e2->setIdentifiers("sizex","BADID");

    success = g->addEdge(e2,n1,n2);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    ::fwData::Edge::sptr e3( ::fwData::Edge::New() );
    e3->setIdentifiers("BADID","threshold");

    success = g->addEdge(e3,n1,n2);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    ::fwData::Node::sptr n4( ::fwData::Node::New() );
    ::fwData::Port::sptr p4( ::fwData::Port::New() );
    p4->setIdentifier("threshold");
    p4->setType("BADTYPE");
    n4->addInputPort( p4 );

    success = g->addNode( n4 );
    CPPUNIT_ASSERT_EQUAL( success ,  true );
    CPPUNIT_ASSERT_EQUAL( (size_t)3, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    // G :
    // n1, n2, n4
    // e1 : n1 -> n2

    ::fwData::Edge::sptr e4( ::fwData::Edge::New() );
    e4->setIdentifiers("sizex","threshold");

    success = g->addEdge(e4,n1,n4);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)3, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );
}

void GraphTest::limitCase2()
{
    // G :
    // n1 --e1--> n2
    using namespace fwData;
    ::fwData::Graph::sptr g( ::fwData::Graph::New() );

    ::fwData::Node::sptr n1( ::fwData::Node::New() );
    ::fwData::Port::sptr p1( ::fwData::Port::New() );
    p1->setIdentifier("sizex");
    p1->setType("float");
    n1->addOutputPort( p1 );
    g->addNode(n1);

    ::fwData::Node::sptr n2( ::fwData::Node::New() );
    ::fwData::Port::sptr p2( ::fwData::Port::New() );
    p2->setIdentifier("threshold");
    p2->setType("float");
    n2->addInputPort( p2 );
    g->addNode(n2);

    ::fwData::Edge::sptr e1( ::fwData::Edge::New() );
    e1->setIdentifiers("sizex","threshold");
    g->addEdge(e1,n1,n2);

    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    bool success;
    success = g->removeNode(n1);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    ::fwData::Edge::sptr e2( ::fwData::Edge::New() );
    e2->setIdentifiers("sizex","threshold");


    success = g->removeEdge(e2);
    CPPUNIT_ASSERT_EQUAL( success ,  false );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, g->getNbNodes() );
    CPPUNIT_ASSERT_EQUAL( (size_t)1, g->getNbEdges() );

    ::fwData::Node::sptr nullNode;
    CPPUNIT_ASSERT_EQUAL( g->getSourceNode(e2), nullNode );
    CPPUNIT_ASSERT_EQUAL( g->getDestinationNode(e2), nullNode );
}

//------------------------------------------------------------------------------

} //namespace ut
} //namespace fwData
