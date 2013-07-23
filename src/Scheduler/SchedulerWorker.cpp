/*
 * Copyright (c) 2013 Ghrum Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Scheduler/SchedulerWorker.hpp>
#include <Types.hpp>
#include <chrono>

using namespace Ghrum;

/////////////////////////////////////////////////////////////////
// {@see SchedulerWorker::SchedulerWorker} //////////////////////
/////////////////////////////////////////////////////////////////
SchedulerWorker::SchedulerWorker(boost::asio::io_service * service)
    : service_(service), busy_(false), available_(true), thread_(
        new boost::thread(Delegate<void()>(this, &SchedulerWorker::run))) {
}

/////////////////////////////////////////////////////////////////
// {@see SchedulerWorker::~SchedulerWorker} /////////////////////
/////////////////////////////////////////////////////////////////
SchedulerWorker::~SchedulerWorker() {
    setCancelled();
    waitForWorker();
}

/////////////////////////////////////////////////////////////////
// {@see SchedulerWorker::run} //////////////////////////////////
/////////////////////////////////////////////////////////////////
void SchedulerWorker::run() {
    boost::system::error_code errorCode;

    // Run the completetion handler, until the platform invoke
    // this worker to not been active any more by joining it.
    while (available_) {
        try {
            // Start the tick time.
            auto start = std::chrono::steady_clock::now();

            // Poll the io_service once from the worker, if
            // we had work, then add tick count into uptime.
            if ( service_->poll_one(errorCode) ) {
                uptime_ += std::chrono::duration_cast<std::chrono::milliseconds>(
                               std::chrono::steady_clock::now() - start).count();
            }

            // Check if there was an error.
            if (errorCode) {
                BOOST_LOG_TRIVIAL(error)
                        << "Worker has trigger an exception: " << errorCode.message();
            }

            // Check for interrupt handler.
            boost::this_thread::interruption_point();
        } catch (std::exception & ex) {
            BOOST_LOG_TRIVIAL(error)
                    << "Worker has trigger an exception: " << ex.what();
        } catch (boost::thread_interrupted & ex) {
            available_ = false;
        }
    }
}