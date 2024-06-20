#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/utils/web.hpp>
#include <cctype>

#include "CommentCell.h"

using namespace geode::prelude;

bool downloaded = false;
std::set<std::string> LBMOD;
EventListener<web::WebTask> m_listener;

void download_list() {

	if (!downloaded) {

		m_listener.bind([](web::WebTask::Event* e) {
			if (web::WebResponse* res = e->getValue()) {
				log::info("{}", res->string().unwrapOr("eee")); // wowzers found whats printing
				auto data = res->string().unwrapOr("eee");

				std::istringstream iss(data);
				std::string temp_string;
				log::info("Downloaded LBMOD List");

				while (iss >> temp_string) {
					YouTubers.insert(temp_string);
				}
				downloaded = true;

			}
			else if (e->isCancelled()) {
				log::info("Failed to fetch file from GitHub.");
			}
			});

		auto req = web::WebRequest();
		m_listener.setFilter(req.get("https://raw.githubusercontent.com/CutinyGD/Show-Leaderboard-Mods-in-comments/main/names.txt"));
	}
}