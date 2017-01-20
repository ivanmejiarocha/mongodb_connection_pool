//
// Copyright (c) 2017, ivmeroLabs.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this 
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify, 
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so, subject to the following 
// conditions:

// The above copyright notice and this permission notice shall be included in all copies 
// or substantial portions of the Software. 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/pool.hpp>

#include "mongodb_pool_config.hpp"

/*!
 * MongodbPoolSingleton
 * SIngleton that provides connections from mongocxx::pool
 */
class MongodbPoolSingleton {
   static std::unique_ptr<MongodbPoolSingleton> _instance;
   static std::once_flag _onceFlag;   

   std::unique_ptr<mongocxx::pool> _connectionPool;

   MongodbPoolSingleton(const MongodbPoolSingletonConfiguration & config) {
      mongocxx::instance inst{};
      _connectionPool = std::unique_ptr<mongocxx::pool>( new mongocxx::pool(mongocxx::uri{_config.connstr()}) );
   };

public:
   static MongodbPoolSingletonConfiguration _config;

   static MongodbPoolSingleton & shared() {
      std::call_once(_onceFlag, []{
         _instance.reset(new MongodbPoolSingleton(_config));
      });
      return *_instance;
   }

   mongocxx::pool & connection() const {
      return *_connectionPool;
   }
};