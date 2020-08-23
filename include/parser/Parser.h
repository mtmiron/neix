/**
 * Feed parser class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef neix_PARSER_H
#define neix_PARSER_H

#include <vector>
#include "rapidxml/rapidxml.hpp"
#include "feed/FeedLoader.h"

using namespace std;
using namespace rapidxml;

namespace neix
{
    class Parser
    {
    public:
        explicit Parser(struct rawRss content);
        ~Parser();

        virtual xml_node<>* getFirstNode() = 0;
        xml_node<>* getNextNode();
        virtual char* getFeedTitle() = 0;
        virtual char* getFeedContent() = 0;
        virtual char* getFeedLink() = 0;
        virtual char* getFeedDate() = 0;
        struct rssItem* getFeedItem();

        char* convertHtmlToPlaintext(const char *text);
        char* renderTextToPlaintext(const char *text);
        char* formatTimeString(const char *timeString);
        void setTimeFormatUI(const char *format);
        void setRenderCommand(const char *command);
        char* getTimeFormatUI();
        void applyConfig(const vector<pair<string, string>> config);

    protected:
        xml_document<> xmlDocument;
        xml_node<> *rootNode{};
        xml_node<> *entryNode{};
        char* timeFormatUI;
        char* renderCommand;

        string buildFullRenderCommand(const string& rawFilePath, const string& renderedFilePath);
        bool prepareRawText(const string& rawFilePath, const char *text);
        int renderText(const string& command);
        string getRenderedText(const string& filePath);

        virtual char* getFeedDateFormat() = 0;
        char* getNodeContent(xml_node<> *node);
        char* getNodeAttribute(xml_node<> *node, const char *attribute);
        void loadXml(struct rawRss rawContent);
    };
}

#endif //neix_PARSER_H
