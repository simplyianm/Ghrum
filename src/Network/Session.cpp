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

#include <Network/Session.hpp>

using namespace Ghrum;

/////////////////////////////////////////////////////////////////
// {@see EventManager::emitEvent} ///////////////////////////////
/////////////////////////////////////////////////////////////////
Session::Session(boost::asio::io_service & service, size_t id)
    : ISession(id), socket_(service) {
}

/////////////////////////////////////////////////////////////////
// {@see EventManager::emitEvent} ///////////////////////////////
/////////////////////////////////////////////////////////////////
void Session::disconnect(const std::string & reason) {

}

/////////////////////////////////////////////////////////////////
// {@see EventManager::emitEvent} ///////////////////////////////
/////////////////////////////////////////////////////////////////
std::string Session::getAddress() {
    return socket_.remote_endpoint().address().to_string();
}

/////////////////////////////////////////////////////////////////
// {@see EventManager::emitEvent} ///////////////////////////////
/////////////////////////////////////////////////////////////////
void Session::setProtocol(IProtocol & protocol) {

}

/////////////////////////////////////////////////////////////////
// {@see EventManager::emitEvent} ///////////////////////////////
/////////////////////////////////////////////////////////////////
void Session::start() {

}

/////////////////////////////////////////////////////////////////
// {@see EventManager::emitEvent} ///////////////////////////////
/////////////////////////////////////////////////////////////////
void Session::sendMessage(IMessage & message) {

}