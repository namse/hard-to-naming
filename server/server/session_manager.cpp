#include "stdafx.h"
#include "session_manager.h"

SessionManager * SessionManager::GetManager()
{
	static SessionManager manager;
	return &manager;
}

void SessionManager::Join(Session::SharedPtr session)
{
	std::lock_guard<std::recursive_mutex> lock(sessions_mutex_);
	sessions_.push_back(session);
}

void SessionManager::Leave(Session::SharedPtr session)
{
	std::lock_guard<std::recursive_mutex> lock(sessions_mutex_);

	auto it = std::find(sessions_.begin(), sessions_.end(), session);
	if (it != sessions_.end()) {
		sessions_.erase(it);
	}
	return;
}
