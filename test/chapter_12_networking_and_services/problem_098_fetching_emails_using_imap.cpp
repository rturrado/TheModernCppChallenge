#include "chapter_12_networking_and_services/imap_connection.h"
#include "chapter_12_networking_and_services/problem_098_fetching_emails_using_imap.h"
#include "imap_connection/mock.h"
#include "imap_connection/samples.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>  // make_unique, unique_ptr
#include <sstream>  // istringstream, ostringstream
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>
#include <vector>

using namespace std::string_view_literals;
using namespace tmcppc::imap;
using namespace tmcppc::problem_98;


TEST(read_mailbox_folder, DISABLED_inbox) {
    std::istringstream iss{ "inbox\n" };
    std::ostringstream oss{};
    EXPECT_EQ(read_mailbox_folder(iss, oss), "inbox");
}


TEST(print_mailbox_folders, DISABLED_empty_folders) {
    std::ostringstream oss{};
    print_mailbox_folders(oss, mailbox_folders_t{});
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of folders from the mailbox:\n"
        "\tThere are no folders in the mailbox\n"
    ));
}
TEST(print_mailbox_folders, DISABLED_non_empty_folders) {
    std::ostringstream oss{};
    print_mailbox_folders(oss, mailbox_folders_t{ "inbox", "sent", "trash" });
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of folders from the mailbox:\n"
        "\tinbox\n"
        "\tsent\n"
        "\ttrash\n"
    ));
}


TEST(print_unread_email_ids_from_folder, DISABLED_empty_email_subjects) {
    std::ostringstream oss{};
    print_unread_email_ids_from_folder(oss, "inbox", email_subjects_t{});
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of unread emails from folder 'inbox':\n"
        "\tThere are no unread emails\n"
    ));
}
TEST(print_unread_email_ids_from_folder, DISABLED_non_empty_email_subjects) {
    std::ostringstream oss{};
    print_unread_email_ids_from_folder(oss, "inbox", email_subjects_t{
        "Subject 1: What do you mean, the party of the first part?",
        "Subject 2: No, the first part of the party, of the first part.",
        "Subject 3: I don't like the second party either."
    });
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of unread emails from folder 'inbox':\n"
        "\tSubject 1: What do you mean, the party of the first part?\n"
        "\tSubject 2: No, the first part of the party, of the first part.\n"
        "\tSubject 3: I don't like the second party either.\n"
    ));
}


TEST(test_imap_connection, DISABLED_output_wrong_folder_name) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_mailbox_folders())
        .WillOnce(::testing::Return(R"(* LIST (\HasNoChildren) "/" "test/tmcppc/problem_98")""\r\n"));
    EXPECT_CALL(connector, get_unread_email_ids("wrong_folder_name"sv))
        .WillOnce(::testing::Throw(imap_connection_error{ "Login denied" }));

    std::istringstream iss{ "wrong_folder_name\n" };
    std::ostringstream oss{};
    test_imap_connection(iss, oss, imap_connection{ std::move(connector_up) });

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of folders from the mailbox:\n"
        "\ttest/tmcppc/problem_98\n"
        "Please enter a folder name: "  // wrong_folder_name
        "\tError: Login denied\n"
    ));
}

TEST(test_imap_connection, DISABLED_output) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_mailbox_folders())
        .WillOnce(::testing::Return(R"(* LIST (\HasNoChildren) "/" "test/tmcppc/problem_98")""\r\n"));
    EXPECT_CALL(connector, get_unread_email_ids("test/tmcppc/problem_98"sv))
        .WillOnce(::testing::Return(R"(* SEARCH 1)""\r\n"));
    EXPECT_CALL(connector, get_email("test/tmcppc/problem_98"sv, 1))
        .WillOnce(::testing::Return(samples::email));

    std::istringstream iss{ "test/tmcppc/problem_98\n" };
    std::ostringstream oss{};
    test_imap_connection(iss, oss, imap_connection{ std::move(connector_up) });

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of folders from the mailbox:\n"
        "\ttest/tmcppc/problem_98\n"
        "Please enter a folder name: "  // test/tmcppc/problem_98
        "List of unread emails from folder 'test/tmcppc/problem_98':\n"
        "\tSubject: =?UTF-8?Q?Harry_Potter=E2=80=99s_acceptance_letter_in_Harry_Potter_a?=\n"
    ));
}
