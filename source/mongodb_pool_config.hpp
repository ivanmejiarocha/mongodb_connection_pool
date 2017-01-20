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

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

/*!
 * IMPORTANT:
 *    The configuration file is a JSON with the following format:
 *    { 
 *       "store": { 
 *                   "connstr":"mongodb://<host_name|ip_address>:27017",
 *                   "database":"my_database"
 *                }
 *    }
 */
class MongodbPoolSingletonConfiguration {
   std::string _connstr;
   std::string _database;
public:
   MongodbPoolSingletonConfiguration() : _connstr(""), _database("") { }
   MongodbPoolSingletonConfiguration(const std::string & confpath) {
      using boost::property_tree::ptree;
      ptree pt;
      
      read_json(confpath, pt);
      _connstr = pt.get<std::string>("store.connstr");
      _database = pt.get<std::string>("store.database");
   }

   std::string connstr() const { return _connstr; }
   std::string database() const { return _database; }
};
