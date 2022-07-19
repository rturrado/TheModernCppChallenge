#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies/samples.h"
#include "chapter_09_data_serialization/xml/pugixml_wrapper.h"
#include "chapter_09_data_serialization/xml/movies.h"

#include "pugixml.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std::chrono_literals;
using namespace tmcppc::movies;
using namespace tmcppc::movies::xml;
using namespace tmcppc::pugixml;


// Role
TEST(xml_role, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "role") };
    to_xml(n, samples::role);
	role r{};
	from_xml(n, r);
	EXPECT_EQ(samples::role, r);
}

// Cast
TEST(xml_cast, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "cast") };
    to_xml(n, samples::cast);
    cast c{};
    from_xml(n, c);
    EXPECT_EQ(samples::cast, c);
}

// Director
TEST(xml_director, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "director") };
    to_xml(n, samples::director);
    director d{};
    from_xml(n, d);
    EXPECT_EQ(samples::director, d);
}

// Directors
TEST(xml_directors, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "directors") };
    to_xml(n, samples::directors);
    directors ds{};
    from_xml(n, ds);
    EXPECT_EQ(samples::directors, ds);
}

// Writer
TEST(xml_writer, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "writer") };
    to_xml(n, samples::writer);
    writer w{};
    from_xml(n, w);
    EXPECT_EQ(samples::writer, w);
}

// Writers
TEST(xml_writers, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "writers") };
    to_xml(n, samples::writers);
    writers ws{};
    from_xml(n, ws);
    EXPECT_EQ(samples::writers, ws);
}

// Movie
TEST(xml_movie, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "movie") };
    to_xml(n, samples::movie);
    movie mv{};
    from_xml(n, mv);
    EXPECT_EQ(samples::movie, mv);
}

// Catalog
TEST(xml_catalog, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "catalog") };
    to_xml(n, samples::catalog);
    catalog mvs{};
    from_xml(n, mvs);
    EXPECT_EQ(samples::catalog, mvs);
}

// XML document
TEST(xml_doc, DISABLED_save_to_and_load_from) {
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "test_doc_save_to_and_load_from.xml" };
    doc out_doc{ samples::catalog };
    out_doc.save_to(temp_file_path);
    doc in_doc{};
    in_doc.load_from(temp_file_path);
    EXPECT_EQ(out_doc, in_doc);
}
