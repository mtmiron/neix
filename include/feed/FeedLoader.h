/**
 * Feed loader class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef CRSS_FEEDLOADER_H
#define CRSS_FEEDLOADER_H

#include <string>
#include <sstream>
#include "Feeds.h"

struct rawRss
{
    char *content;
    size_t size;
};

namespace crss
{
    class FeedLoader
    {
    public:
        FeedLoader();
        ~FeedLoader();

        bool loadFeedsFromConfig(Feeds *feeds);
        bool loadArticlesOfFeeds(Feeds *feeds);
        bool load(std::string feedUrl);
        struct rawRss getFeed();
        std::stringstream configPath;

    private:
        std::string url;
        struct rawRss *feed{};

		struct rss* createNewFeed(const char* name, const char* link);
        void resetFeed();
        static size_t curlCalculateMemory(void *content, size_t size, size_t nmemb, void *userp);
        bool loadXml();
    };
}

#endif //CRSS_FEEDLOADER_H
