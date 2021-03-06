/*
 * UserCache.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#include "UserCache.h"
#include "ObjectCounter.h"

using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;

HashMap UserCache::_usersCache;

UserCache::UserCache() {
	CONSTRUCT(L"UserCache");
	_usersCache.Construct(100);
}

UserCache::~UserCache() {
	DESTRUCT(L"UserCache");
}

void UserCache::Put(int userId, JsonObject * userJson) {
	_usersCache.Add(new Integer(userId), userJson);
}

JsonObject * UserCache::Get(const int userId) {
	return dynamic_cast<JsonObject * >(_usersCache.GetValue(Integer(userId)));
}
