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

#include "application.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <fstream>

CONTACTS_NAMESPACE_BEGIN

Application::Preferences::Preferences(const Translator::Language & language,
    const Theme & theme) : language(language), theme(theme) {}
Application::Preferences::~Preferences() {}

Application::Application() {
    preferenceFile = fopen("preferences", "rb+");

    if (preferenceFile != CONTACTS_NULL) {
        fread(&preferences, sizeof(Preferences), 1, preferenceFile);
    }
    else {
        preferenceFile = fopen("preferences", "wb+");

        if (preferenceFile != CONTACTS_NULL)
            fwrite(&preferences, sizeof(Preferences), 1, preferenceFile);
    }

    fclose(preferenceFile);

    translator.setLanguage(preferences.language);

#if _WIN64
    setTheme(preferences.theme);
#endif

    contactCount = 0;
    contactList = new Contact[CONTACTS_MAX_CONTACT_COUNT];

    clear();
}
Application::~Application() {
    if (preferenceFile != CONTACTS_NULL)
        fclose(preferenceFile);

    if (contactList != CONTACTS_NULL)
        delete[] contactList;
}

UInt Application::execute(const Character * message) {
    createTitle(message);

    std::vector<const Character *> menu;
    menu.push_back(Translator::ADD);
    menu.push_back(Translator::EDIT);
    menu.push_back(Translator::DELETE);
    menu.push_back(Translator::CLEAR);
    menu.push_back(Translator::LIST);
    menu.push_back(Translator::SEARCH);
    menu.push_back(Translator::EXPORT);
    menu.push_back(Translator::PREFERENCES);
    menu.push_back(Translator::ABOUT);
    menu.push_back(Translator::EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
    case 1:
        if (contactCount != 10)
            addAction();
        else
            execute(Translator::FULL_MEMORY_ERROR);

        break;
    case 2:
        if (contactCount != 0)
            editAction();
        else
            execute(Translator::NO_CONTACTS_FOUND_WARNING);

        break;
    case 3:
        if (contactCount != 0)
            deleteAction();
        else
            execute(Translator::NO_CONTACTS_FOUND_WARNING);

        break;
    case 4:
        if (contactCount != 0)
            clearAction();
        else
            execute(Translator::NO_CONTACTS_FOUND_WARNING);

        break;
    case 5:
        if (contactCount != 0)
            listAction();
        else
            execute(Translator::NO_CONTACTS_FOUND_WARNING);

        break;
    case 6:
        if (contactCount != 0)
            searchAction();
        else
            execute(Translator::NO_CONTACTS_FOUND_WARNING);

        break;
    case 7:
        if (contactCount != 0)
            exportAction();
        else
            execute(Translator::NO_CONTACTS_FOUND_WARNING);

        break;
    case 8:
        preferencesAction();
        break;
    case 9:
        aboutAction();
        break;
    case 10:
        exitAction();
        break;
    default:
        execute();
    }

    return 0;
}

void Application::setTheme(const Theme & theme) {
    switch (theme) {
    case Theme::Dark:
        system("color 0F");
        break;
    default:
        system("color F0");
    }
}
void Application::requestText(std::string & text) {
    std::getline(std::cin, text);
}
void Application::requestOption() {
    std::string stringOption;

    requestText(stringOption);
    stringOption = stringOption.substr(0, CONTACTS_MAX_OPTION_LENGTH);

    UInt type;
    std::stringstream sstream(stringOption);

    sstream >> std::noskipws >> type;

    option = sstream && sstream.eof() ? std::stoi(stringOption) : 0;
}

void Application::createTitle(const Character * message) {
    clear();

    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
    std::cout << "*                                  " << Translator::CONTACTS;
    std::cout << "                                   *" << std::endl;
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");

    separator();

    if (message != CONTACTS_NULL) {
        print(message);
        separator();
    }
}
void Application::createMenu(const std::vector<const Character *> & menu) {
    for (UInt i = 0; i < menu.size(); i++)
        std::cout << i + 1 << ". " << menu[i] << std::endl;
}
void Application::print(const Character * string) {
    std::cout << string << std::endl;
}
void Application::separator() {
    std::cout << std::endl;
}
void Application::clear() {
#ifdef _WIN64
    system("cls");
#else
    system("clear");
#endif
}

void Application::getSortedReferences(ContactReference * references, Bool descending) {
    UInt n = contactCount;
    UInt t;

    Bool c;

    for (UInt i = 0; i < contactCount; i++)
        references[i] = &contactList[i];

    do {
        t = 0;

        for (UInt i = 1; i < n; i++) {
            c = (*references[i - 1]).compare(*references[i]) < 0;

            if (c && descending || !c && !descending) {
                std::swap(references[i - 1], references[i]);
                t = i;
            }
        }

        n = t;
    } while (n != 0);
}

void Application::addAction() {
    createTitle(Translator::ADD_MESSAGE);

    Contact contact;
    std::vector<const Character *> menu;

    std::cin >> contact;
    separator();

    if (!contact.isValid()) {
        print(Translator::INVALID_CONTACT_ERROR);
        separator();

        menu.push_back(Translator::CONTINUE);
        menu.push_back(Translator::CANCEL);
        menu.push_back(Translator::EXIT);

        createMenu(menu);
        separator();

        requestOption();
        separator();

        switch (option) {
        case 1:
            addAction();
            break;
        case 2:
            execute();
            break;
        case 3:
            exitAction();
            break;
        default:
            addAction();
        }
    }
    else {
        menu.push_back(Translator::ADD);
        menu.push_back(Translator::CANCEL);
        menu.push_back(Translator::EXIT);

        createMenu(menu);
        separator();

        requestOption();
        separator();

        switch (option) {
        case 1:
            contactList[contactCount++] = contact;
            execute();

            break;
        case 2:
            execute();
            break;
        case 3:
            exitAction();
            break;
        default:
            addAction();
        }
    }
}
void Application::editAction() {
    createTitle(Translator::EDIT_MESSAGE);

    print(Translator::NAME);

    std::string name;

    requestText(name);
    separator();

    std::vector<const Character *> menu;
    std::vector<Contact *> results;

    for (UInt i = 0; i < contactCount; i++) {
        if (contactList[i].compare(name.c_str()) == 0) {
            results.push_back(&contactList[i]);

            std::cout << results.size() << ". " << contactList[i] << std::endl << std::endl;
        }
    }

    if (results.size() == 0) {
        print(Translator::INVALID_CONTACT_ERROR);
        separator();

        menu.push_back(Translator::CONTINUE);
        menu.push_back(Translator::CANCEL);
        menu.push_back(Translator::EXIT);

        createMenu(menu);
        separator();

        requestOption();
        separator();

        switch (option) {
        case 1:
            editAction();
            break;
        case 2:
            execute();
            break;
        case 3:
            exitAction();
            break;
        default:
            editAction();
        }
    }
    else {
        print(Translator::SELECT_MESSAGE);

        requestOption();
        separator();

        if (option < 1 || option > results.size()) {
            print(Translator::INVALID_CONTACT_ERROR);
            separator();

            menu.push_back(Translator::CONTINUE);
            menu.push_back(Translator::CANCEL);
            menu.push_back(Translator::EXIT);

            createMenu(menu);
            separator();

            requestOption();
            separator();

            switch (option) {
            case 1:
                editAction();
                break;
            case 2:
                execute();
                break;
            case 3:
                exitAction();
                break;
            default:
                editAction();
            }
        }
        else {
            UInt index = option - 1;
            Contact contact;

            std::cin >> contact;
            separator();

            if (!contact.isValid()) {
                print(Translator::INVALID_CONTACT_ERROR);
                separator();

                menu.push_back(Translator::CONTINUE);
                menu.push_back(Translator::CANCEL);
                menu.push_back(Translator::EXIT);

                createMenu(menu);
                separator();

                requestOption();
                separator();

                switch (option) {
                case 1:
                    editAction();
                    break;
                case 2:
                    execute();
                    break;
                case 3:
                    exitAction();
                    break;
                default:
                    editAction();
                }
            }
            else {
                menu.push_back(Translator::EDIT);
                menu.push_back(Translator::CANCEL);
                menu.push_back(Translator::EXIT);

                createMenu(menu);
                separator();

                requestOption();
                separator();

                switch (option) {
                case 1:
                    *results[index] = contact;
                    execute();

                    break;
                case 2:
                    execute();
                    break;
                case 3:
                    exitAction();
                    break;
                default:
                    editAction();
                }
            }
        }
    }
}
void Application::deleteAction() {
    createTitle(Translator::DELETE_MESSAGE);

    print(Translator::NAME);

    std::string name;

    requestText(name);
    separator();

    std::vector<const Character *> menu;
    std::vector<UInt> results;

    for (UInt i = 0; i < contactCount; i++) {
        if (contactList[i].compare(name.c_str()) == 0) {
            results.push_back(i);

            std::cout << results.size() << ". " << contactList[i] << std::endl << std::endl;
        }
    }

    if (results.size() == 0) {
        print(Translator::INVALID_CONTACT_ERROR);
        separator();

        menu.push_back(Translator::CONTINUE);
        menu.push_back(Translator::CANCEL);
        menu.push_back(Translator::EXIT);

        createMenu(menu);
        separator();

        requestOption();
        separator();

        switch (option) {
        case 1:
            deleteAction();
            break;
        case 2:
            execute();
            break;
        case 3:
            exitAction();
            break;
        default:
            deleteAction();
        }
    }
    else {
        print(Translator::SELECT_MESSAGE);

        requestOption();
        separator();

        if (option < 1 || option > results.size()) {
            print(Translator::INVALID_CONTACT_ERROR);
            separator();

            menu.push_back(Translator::CONTINUE);
            menu.push_back(Translator::CANCEL);
            menu.push_back(Translator::EXIT);

            createMenu(menu);
            separator();

            requestOption();
            separator();

            switch (option) {
            case 1:
                deleteAction();
                break;
            case 2:
                execute();
                break;
            case 3:
                exitAction();
                break;
            default:
                deleteAction();
            }
        }
        else {
            UInt index = results[option - 1] + 1;

            menu.push_back(Translator::DELETE);
            menu.push_back(Translator::CANCEL);
            menu.push_back(Translator::EXIT);

            createMenu(menu);
            separator();

            requestOption();
            separator();

            switch (option) {
            case 1:
                for (UInt i = index; i < contactCount; i++)
                    contactList[i - 1] = contactList[i];

                contactCount--;
                execute();

                break;
            case 2:
                execute();
                break;
            case 3:
                exitAction();
                break;
            default:
                deleteAction();
            }
        }
    }
}
void Application::clearAction() {
    createTitle(Translator::CLEAR_MESSAGE);

    std::vector<const Character *> menu;
    menu.push_back(Translator::YES);
    menu.push_back(Translator::NO);
    menu.push_back(Translator::EXIT);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    switch (option) {
    case 1:
        contactCount = 0;
        execute();

        break;
    case 2:
        execute();
        break;
    case 3:
        exitAction();
        break;
    default:
        clearAction();
    }
}
void Application::searchAction() {
    createTitle(Translator::SEARCH_MESSAGE);

    print(Translator::NAME);

    std::string name;

    requestText(name);
    separator();

    UInt count = 1;

    for (UInt i = 0; i < contactCount; i++) {
        if (contactList[i].compare(name.c_str()) == 0)
            std::cout << count++ << ". " << contactList[i] << std::endl << std::endl;
    }

    if (count == 1) {
        print(Translator::NO_CONTACTS_FOUND_WARNING);
        separator();
    }

    std::vector<const Character *> menu;
    menu.push_back(Translator::OK);
    menu.push_back(Translator::SEARCH);
    menu.push_back(Translator::EXIT);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    switch (option) {
    case 1:
        execute();
        break;
    case 2:
        searchAction();
        break;
    case 3:
        exitAction();
        break;
    default:
        searchAction();
    }
}
void Application::listAction() {
    createTitle(Translator::LIST_MESSAGE);

    std::vector<const Character *> menu;
    menu.push_back(Translator::ASCENDING);
    menu.push_back(Translator::DESCENDING);
    menu.push_back(Translator::INSERTION);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    if (option == 1 || option == 2) {
        ContactReference * references = new ContactReference[contactCount];
        getSortedReferences(references, option - 1);

        for (UInt i = 0; i < contactCount; i++)
            std::cout << i + 1 << ". " << *references[i] << std::endl << std::endl;

        delete[] references;
    }
    else if (option == 3) {
        for (UInt i = 0; i < contactCount; i++)
            std::cout << i + 1 << ". " << contactList[i] << std::endl << std::endl;
    }
    else {
        listAction();

        return;
    }

    menu.clear();
    menu.push_back(Translator::OK);
    menu.push_back(Translator::EXIT);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    switch (option) {
    case 1:
        execute();
        break;
    case 2:
        exitAction();
        break;
    default:
        listAction();
    }
}
void Application::exportAction() {
    createTitle(Translator::EXPORT_MESSAGE);

    std::string filename;
    std::fstream file;

    requestText(filename);
    separator();

    print(Translator::SORT_MESSAGE);
    separator();

    std::vector<const Character *> menu;
    menu.push_back(Translator::ASCENDING);
    menu.push_back(Translator::DESCENDING);
    menu.push_back(Translator::INSERTION);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    UInt sortOption = option - 1;

    if (option < 1 || option > 3) {
        exportAction();

        return;
    }

    menu.clear();
    menu.push_back(Translator::EXPORT);
    menu.push_back(Translator::CANCEL);
    menu.push_back(Translator::EXIT);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    switch (option) {
    case 1:
        file.open(filename, std::fstream::out);

        if (file.is_open()) {
            ContactReference * references = CONTACTS_NULL;

            if (sortOption != 2) {
                references = new ContactReference[contactCount];
                getSortedReferences(references, sortOption);
            }

            for (UInt i = 0; i < contactCount; i++) {
                if (sortOption != 2)
                    file << *references[i];
                else
                    file << contactList[i];

                if (i != contactCount - 1)
                    file << std::endl << std::endl;
            }

            file.close();

            if (sortOption != 2)
                delete[] references;

            execute();
        }
        else
            exportAction();

        break;
    case 2:
        execute();
        break;
    case 3:
        exitAction();
        break;
    default:
        exportAction();
    }
}
void Application::preferencesAction() {
    createTitle(Translator::LANGUAGE_MESSAGE);

    std::vector<const Character *> menu;
    menu.push_back(Translator::ENGLISH);
    menu.push_back(Translator::PORTUGUESE);
    menu.push_back(Translator::DEFAULT);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    if (option < 1 || option > menu.size()) {
        preferencesAction();

        return;
    }

    preferences.language = (Translator::Language)(option - 1);

#ifdef _WIN64
    print(Translator::THEME_MESSAGE);
    separator();

    menu.clear();
    menu.push_back(Translator::LIGHT);
    menu.push_back(Translator::DARK);
    menu.push_back(Translator::DEFAULT);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    if (option < 1 || option > menu.size()) {
        preferencesAction();

        return;
    }

    preferences.theme = (Theme)(option - 1);
#endif

    menu.clear();
    menu.push_back(Translator::SAVE);
    menu.push_back(Translator::CANCEL);
    menu.push_back(Translator::EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
    case 1:
        preferenceFile = fopen("preferences", "wb+");

        if (preferenceFile != CONTACTS_NULL)
            fwrite(&preferences, sizeof(Preferences), 1, preferenceFile);

        fclose(preferenceFile);

        translator.setLanguage(preferences.language);

#ifdef _WIN64
        setTheme(preferences.theme);
#endif

        execute();

        break;
    case 2:
        execute();
        break;
    case 3:
        exitAction();
        break;
    default:
        preferencesAction();
    }
}
void Application::aboutAction() {
    createTitle(Translator::ABOUT_MESSAGE);

    print(Translator::COPYRIGHT_MESSAGE);
    print(Translator::LICENSE_MESSAGE);
    separator();

    std::vector<const Character *> menu;
    menu.push_back(Translator::OK);
    menu.push_back(Translator::EXIT);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    switch (option) {
    case 1:
        execute();
        break;
    case 2:
        exitAction();
        break;
    default:
        aboutAction();
    }
}
void Application::exitAction() {
    createTitle(Translator::EXIT_MESSAGE);

    std::vector<const Character *> menu;
    menu.push_back(Translator::YES);
    menu.push_back(Translator::NO);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    switch (option) {
    case 1:
        return;
        break;
    case 2:
        execute();
        break;
    default:
        exitAction();
    }
}

CONTACTS_NAMESPACE_END