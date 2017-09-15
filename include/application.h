// Copyright (c) 2017, Danilo Peixoto. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef CONTACTS_APPLICATION_H
#define CONTACTS_APPLICATION_H

#include "global.h"
#include "types.h"
#include "contact.h"
#include "translator.h"
#include <cstdio>
#include <vector>
#include <string>

CONTACTS_NAMESPACE_BEGIN

class Application {
public:
    enum Theme {
        Light = 0,
        Dark,
        Default
    };

    struct Preferences {
        Preferences(const Translator::Language & = Translator::Language::Default,
            const Theme & = Theme::Default);
        ~Preferences();

        Translator::Language language;
        Theme theme;
    };

    Application();
    ~Application();

    UInt execute(const Character * = CONTACTS_NULL);

private:
    typedef Contact * ContactReference;

    UInt option;

    Translator translator;
    Preferences preferences;

    FILE * preferenceFile;

    UInt contactCount;
    Contact * contactList;

    void setTheme(const Theme &);
    void requestText(std::string &);
    void requestOption();

    void createTitle(const Character * = CONTACTS_NULL);
    void createMenu(const std::vector<const Character *> &);
    void print(const Character *);
    void separator();
    void clear();

    void getSortedReferences(ContactReference *, Bool);

    void addAction();
    void editAction();
    void deleteAction();
    void clearAction();
    void listAction();
    void searchAction();
    void exportAction();
    void preferencesAction();
    void aboutAction();
    void exitAction();
};

CONTACTS_NAMESPACE_END

#endif