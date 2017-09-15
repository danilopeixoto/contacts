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

#ifndef CONTACTS_TRANSLATOR_H
#define CONTACTS_TRANSLATOR_H

#include "global.h"
#include "types.h"

CONTACTS_NAMESPACE_BEGIN

class Translator {
public:
    enum Language {
        English = 0,
        Portuguese,
        Default
    };

    static Character * ADD;
    static Character * EDIT;
    static Character * DELETE;
    static Character * CLEAR;
    static Character * LIST;
    static Character * SEARCH;
    static Character * EXPORT;
    static Character * PREFERENCES;
    static Character * ABOUT;
    static Character * EXIT;

    static Character * ADD_MESSAGE;
    static Character * EDIT_MESSAGE;
    static Character * SELECT_MESSAGE;
    static Character * DELETE_MESSAGE;
    static Character * CLEAR_MESSAGE;
    static Character * LIST_MESSAGE;
    static Character * SEARCH_MESSAGE;
    static Character * EXPORT_MESSAGE;
    static Character * SORT_MESSAGE;
    static Character * LANGUAGE_MESSAGE;
    static Character * THEME_MESSAGE;
    static Character * ABOUT_MESSAGE;
    static Character * COPYRIGHT_MESSAGE;
    static Character * LICENSE_MESSAGE;
    static Character * EXIT_MESSAGE;

    static Character * NO_CONTACTS_FOUND_WARNING;

    static Character * INVALID_CONTACT_ERROR;
    static Character * FULL_MEMORY_ERROR;

    static Character * CONTACTS;
    static Character * NAME;
    static Character * TELEPHONE_NUMBER;
    static Character * ASCENDING;
    static Character * DESCENDING;
    static Character * INSERTION;
    static Character * ENGLISH;
    static Character * PORTUGUESE;
    static Character * LIGHT;
    static Character * DARK;
    static Character * DEFAULT;
    static Character * SAVE;

    static Character * YES;
    static Character * NO;
    static Character * OK;
    static Character * CANCEL;
    static Character * CONTINUE;

    Translator();
    ~Translator();

    Translator & setLanguage(const Language &);
    Language getLanguage() const;

private:
    static Language language;

    Translator & setEnglishLanguage();
    Translator & setPortugueseLanguage();
};

CONTACTS_NAMESPACE_END

#endif