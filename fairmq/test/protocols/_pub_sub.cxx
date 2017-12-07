/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runner.h"
#include <fairmq/Tools.h>
#include <gtest/gtest.h>
#include <sstream> // std::stringstream
#include <thread>

namespace
{

using namespace std;
using namespace fair::mq::test;

auto RunPubSub(string transport) -> void
{
    size_t session{fair::mq::tools::UuidHash()};

    auto pub = execute_result{"", 0};
    thread pub_thread([&]() {
        stringstream cmd;
        cmd << runTestDevice << " --id pub_" << transport << " --control static --verbosity DEBUG "
        << "--session " << session << " --log-color false --mq-config \"" << mqConfig << "\"";
        pub = execute(cmd.str(), "[PUB]");
    });

    auto sub1 = execute_result{"", 0};
    thread sub1_thread([&]() {
        stringstream cmd;
        cmd << runTestDevice << " --id sub_1" << transport << " --control static --verbosity DEBUG "
        << "--session " << session << " --log-color false --mq-config \"" << mqConfig << "\"";
        sub1 = execute(cmd.str(), "[SUB1]");
    });

    auto sub2 = execute_result{"", 0};
    thread sub2_thread([&]() {
        stringstream cmd;
        cmd << runTestDevice << " --id sub_2" << transport << " --control static --verbosity DEBUG "
        << "--session " << session << " --log-color false --mq-config \"" << mqConfig << "\"";
        sub2 = execute(cmd.str(), "[SUB2]");
    });

    pub_thread.join();
    sub1_thread.join();
    sub2_thread.join();
    cerr << pub.error_out << sub1.error_out << sub2.error_out;

    exit(pub.exit_code + sub1.exit_code + sub2.exit_code);
}

TEST(PubSub, ZeroMQ)
{
    EXPECT_EXIT(RunPubSub("zeromq"), ::testing::ExitedWithCode(0), "PUB-SUB test successfull");
}

#ifdef NANOMSG_FOUND
TEST(PubSub, Nanomsg)
{
    EXPECT_EXIT(RunPubSub("nanomsg"), ::testing::ExitedWithCode(0), "PUB-SUB test successfull");
}
#endif /* NANOMSG_FOUND */

} // namespace