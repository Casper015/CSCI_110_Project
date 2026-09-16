#pragma once
#include "httplib.h"
#include "json.hpp"
#include "rapidxml.hpp"

using namespace std;

void getRandomJoke(string&, string&);
void getSongLyrics(string, string, string&);

void getRandomJoke(string& setup, string& punchline)
{
	httplib::Client cli("http://official-joke-api.appspot.com");

	auto res = cli.Get("/random_joke");
	if (!res)
	{
		const auto err = res.error();
		cerr << "HTTP error: " << httplib::to_string(err) << endl;
		return;
	}

	if (res->status != 200)
	{
		cerr << "HTTP Status: " << res->status << endl;
		return;
	}

	auto data = nlohmann::json::parse(res->body);
	setup = data["setup"];
	punchline = data["punchline"];
}

void getSongLyrics(string artist, string song, string& lyrics)
{
	httplib::Client cli("http://api.chartlyrics.com");
	httplib::Params params
	{
		{ "artist", artist },
		{ "song", song }
	};
	auto res = cli.Get("/apiv1.asmx/SearchLyricDirect", params, {});
	if (!res)
	{
		const auto err = res.error();
		cerr << "HTTP error: " << httplib::to_string(err) << endl;
		return;
	}

	if (res->status != 200)
	{
		cerr << "HTTP Status: " << res->status << endl;
		return;
	}
	rapidxml::xml_document<> doc;
	doc.parse<0>(res->body.data());
	auto node = doc.first_node()->first_node("Lyric");
	lyrics = node->value();
}
