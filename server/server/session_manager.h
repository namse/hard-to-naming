#pragma once
#include "session.h"

class SessionManager
{
public:
	static SessionManager * GetManager();

	void Join(Session::SharedPtr session);
	void Leave(Session::SharedPtr session);
private:

	std::vector<Session::SharedPtr> sessions_;
	std::recursive_mutex sessions_mutex_;
};
