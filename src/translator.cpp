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

#include "translator.h"
#include <locale>

CONTACTS_NAMESPACE_BEGIN

Character * Translator::ADD;
Character * Translator::EDIT;
Character * Translator::DELETE;
Character * Translator::CLEAR;
Character * Translator::LIST;
Character * Translator::SEARCH;
Character * Translator::EXPORT;
Character * Translator::PREFERENCES;
Character * Translator::ABOUT;
Character * Translator::EXIT;

Character * Translator::ADD_MESSAGE;
Character * Translator::EDIT_MESSAGE;
Character * Translator::SELECT_MESSAGE;
Character * Translator::DELETE_MESSAGE;
Character * Translator::CLEAR_MESSAGE;
Character * Translator::LIST_MESSAGE;
Character * Translator::SEARCH_MESSAGE;
Character * Translator::EXPORT_MESSAGE;
Character * Translator::LANGUAGE_MESSAGE;
Character * Translator::THEME_MESSAGE;
Character * Translator::ABOUT_MESSAGE;
Character * Translator::COPYRIGHT_MESSAGE;
Character * Translator::LICENSE_MESSAGE;
Character * Translator::EXIT_MESSAGE;

Character * Translator::NO_CONTACTS_FOUND_WARNING;

Character * Translator::INVALID_CONTACT_ERROR;
Character * Translator::FULL_MEMORY_ERROR;

Character * Translator::CONTACTS;
Character * Translator::NAME;
Character * Translator::TELEPHONE_NUMBER;
Character * Translator::ENGLISH;
Character * Translator::PORTUGUESE;
Character * Translator::LIGHT;
Character * Translator::DARK;
Character * Translator::DEFAULT;
Character * Translator::SAVE;

Character * Translator::YES;
Character * Translator::NO;
Character * Translator::OK;
Character * Translator::CANCEL;
Character * Translator::CONTINUE;

Translator::Language Translator::language;

Translator::Translator() {
    setEnglishLanguage();
}
Translator::~Translator() {}

Translator & Translator::setLanguage(const Language & language) {
    switch (language) {
    case Language::Portuguese:
        setPortugueseLanguage();
        break;
    default:
        setEnglishLanguage();
    }

    return *this;
}
Translator::Language Translator::getLanguage() const {
    return language;
}

Translator & Translator::setEnglishLanguage() {
    language = English;
    setlocale(LC_ALL, "english");

    ADD = "Add";
    EDIT = "Edit";
    DELETE = "Delete";
    CLEAR = "Clear";
    LIST = "List";
    SEARCH = "Search";
    EXPORT = "Export";
    PREFERENCES = "Preferences";
    ABOUT = "About";
    EXIT = "Exit";

    ADD_MESSAGE = "Add a new contact:";
    EDIT_MESSAGE = "Enter a contact name to edit:";
    SELECT_MESSAGE = "Select a contact:";
    DELETE_MESSAGE = "Enter a contact name to delete:";
    CLEAR_MESSAGE = "Are you sure you want to clear the contact list?";
    LIST_MESSAGE = "Contacts:";
    SEARCH_MESSAGE = "Enter a contact name to search:";
    EXPORT_MESSAGE = "Enter a filename to export the contact list:";
    LANGUAGE_MESSAGE = "Select an application language:";
    THEME_MESSAGE = "Select an application theme:";
    ABOUT_MESSAGE = "A simple application to manage contacts.";
    COPYRIGHT_MESSAGE = "Copyright (c) 2017, Danilo Peixoto. All rights reserved.";
    LICENSE_MESSAGE = "Software developed under the BSD-3-Clause license.";
    EXIT_MESSAGE = "Are you sure you want to close the application?";

    NO_CONTACTS_FOUND_WARNING = "No contacts found.";

    INVALID_CONTACT_ERROR = "Error: invalid contact.";
    FULL_MEMORY_ERROR = "Error: full memory.";

    CONTACTS = "CONTACTS";
    NAME = "Name:";
    TELEPHONE_NUMBER = "Telephone number:";
    ENGLISH = "English";
    PORTUGUESE = "Portuguese";
    LIGHT = "Light";
    DARK = "Dark";
    DEFAULT = "Default";
    SAVE = "Save";

    YES = "Yes";
    NO = "No";
    OK = "OK";
    CANCEL = "Cancel";
    CONTINUE = "Continue";

    return *this;
}
Translator & Translator::setPortugueseLanguage() {
    language = Portuguese;
    setlocale(LC_ALL, "portuguese");

    ADD = "Adicionar";
    EDIT = "Editar";
    DELETE = "Deletar";
    CLEAR = "Limpar";
    LIST = "Listar";
    SEARCH = "Perquisar";
    EXPORT = "Exportar";
    PREFERENCES = "Preferências";
    ABOUT = "Sobre";
    EXIT = "Sair";

    ADD_MESSAGE = "Adicione um novo contato:";
    EDIT_MESSAGE = "Insira um nome de contato para editar:";
    SELECT_MESSAGE = "Selecione um contato:";
    DELETE_MESSAGE = "Insira um nome de contato para deletar:";
    CLEAR_MESSAGE = "Você tem certeza que deseja limpar a lista de contatos?";
    LIST_MESSAGE = "Contatos:";
    SEARCH_MESSAGE = "Insira um nome de contato para pesquisar:";
    EXPORT_MESSAGE = "Insira um nome de arquivo para exportar a lista de contatos:";
    LANGUAGE_MESSAGE = "Selecione um idioma para aplicação:";
    THEME_MESSAGE = "Selecione um tema para aplicação:";
    ABOUT_MESSAGE = "Uma simples aplicação para gerenciar contatos.";
    COPYRIGHT_MESSAGE = "Copyright (c) 2017, Danilo Peixoto. Todos os direitos reservados.";
    LICENSE_MESSAGE = "Programa desenvolvido sob a licença BSD-3-Clause.";
    EXIT_MESSAGE = "Você tem certeza que deseja fechar a aplicação?";

    NO_CONTACTS_FOUND_WARNING = "Nenhum contato encontrado.";

    INVALID_CONTACT_ERROR = "Erro: contato inválido.";
    FULL_MEMORY_ERROR = "Erro: memória cheia.";

    CONTACTS = "CONTATOS";
    NAME = "Nome:";
    TELEPHONE_NUMBER = "Número de telefone:";
    ENGLISH = "Inglês";
    PORTUGUESE = "Português";
    LIGHT = "Claro";
    DARK = "Escuro";
    DEFAULT = "Padrão";
    SAVE = "Salvar";

    YES = "Sim";
    NO = "Não";
    OK = "OK";
    CANCEL = "Cancelar";
    CONTINUE = "Continuar";

    return *this;
}

CONTACTS_NAMESPACE_END