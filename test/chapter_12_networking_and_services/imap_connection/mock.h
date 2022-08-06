#pragma once

#include "chapter_12_networking_and_services/imap_connection.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <string_view>


namespace tmcppc::imap {
    class connector_mock : public connector_adaptor {
    public:
        MOCK_METHOD(std::string, get_mailbox_folders, (), (const, override));
        MOCK_METHOD(std::string, get_unread_email_ids, (std::string_view folder), (const, override));
        MOCK_METHOD(std::string, get_email, (std::string_view folder, size_t id), (const, override));
    };
}  // namespace tmcppc::imap
