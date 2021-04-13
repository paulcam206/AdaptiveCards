// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"
#include "HostConfig.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;

namespace AdaptiveCardsSharedModelUnitTest
{
    TEST_CLASS(HostConfigTest)
    {
    public:
        TEST_METHOD(ParseHeadingConfig)
        {
            // Test default values
            HostConfig hostConfig;
            HeadingsConfig headingConfig = hostConfig.GetHeadings();

            Assert::AreEqual(2U, headingConfig.level);
            Assert::IsTrue(ForegroundColor::Default == headingConfig.defaultTextBlockConfig.color);
            Assert::IsTrue(FontType::Default == headingConfig.defaultTextBlockConfig.fontType);
            Assert::IsFalse(headingConfig.defaultTextBlockConfig.isSubtle);
            Assert::AreEqual(~0U, headingConfig.defaultTextBlockConfig.maxWidth);
            Assert::IsTrue(TextSize::Medium == headingConfig.defaultTextBlockConfig.size);
            Assert::IsTrue(TextWeight::Bolder == headingConfig.defaultTextBlockConfig.weight);
            Assert::IsTrue(headingConfig.defaultTextBlockConfig.wrap);

            // Test host config parsed from json
            std::string testjson{ R"(
                {
                  "headings": {
                    "level": 5,
                    "defaultTextBlockConfig": {
                      "color": "Good",
                      "fontType": "Monospace",
                      "isSubtle": true,
                      "maxWidth": 100,
                      "size": "Large",
                      "weight": "Lighter",
                      "wrap": false
                    }
                  }
                }
            )"};

            headingConfig = HostConfig::DeserializeFromString(testjson).GetHeadings();

            Assert::AreEqual(5U, headingConfig.level);
            Assert::IsTrue(ForegroundColor::Good == headingConfig.defaultTextBlockConfig.color);
            Assert::IsTrue(FontType::Monospace == headingConfig.defaultTextBlockConfig.fontType);
            Assert::IsTrue(headingConfig.defaultTextBlockConfig.isSubtle);
            Assert::AreEqual(100U, headingConfig.defaultTextBlockConfig.maxWidth);
            Assert::IsTrue(TextSize::Large == headingConfig.defaultTextBlockConfig.size);
            Assert::IsTrue(TextWeight::Lighter == headingConfig.defaultTextBlockConfig.weight);
            Assert::IsFalse(headingConfig.defaultTextBlockConfig.wrap);
        }
    };
}
