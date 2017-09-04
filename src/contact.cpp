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

#include "contact.h"
#include "common.h"
#include "translator.h"
#include <cctype>

CONTACTS_NAMESPACE_BEGIN

Contact::Contact() : name(CONTACTS_NULL), telephoneNumber(CONTACTS_NULL) {}
Contact::Contact(const Contact & contact) {
    allocate(contact.getName(), contact.getTelephoneNumber());
}
Contact::Contact(const Character * name, const Character * telephoneNumber) {
    allocate(name, telephoneNumber);
}
Contact::~Contact() {
    deallocate();
}

Contact & Contact::operator =(const Contact & contact) {
    deallocate();
    allocate(contact.getName(), contact.getTelephoneNumber());

    return *this;
}
Bool Contact::operator ==(const Contact & contact) const {
    return contacts::compare(name, contact.getName()) == 0
        && contacts::compare(telephoneNumber, contact.getTelephoneNumber()) == 0;
}
Bool Contact::operator !=(const Contact & contact) const {
    return !(*this == contact);
}
std::istream & operator >>(std::istream & lhs, Contact & rhs) {
    Character * name = new Character[CONTACTS_MAX_NAME_LENGTH + 1];
    Character * telephoneNumber = new Character[CONTACTS_MAX_TELEPHONE_LENGTH + 1];

    std::cout << Translator::NAME << ' ';
    lhs.getline(name, CONTACTS_MAX_NAME_LENGTH);

    std::cout << Translator::TELEPHONE_NUMBER << ' ';
    lhs.getline(telephoneNumber, CONTACTS_MAX_TELEPHONE_LENGTH);

    rhs.setName(name);
    rhs.setTelephoneNumber(telephoneNumber);

    delete[] name;
    delete[] telephoneNumber;

    return lhs;
}
std::ostream & operator <<(std::ostream & lhs, const Contact & rhs) {
    if (rhs.hasName())
        lhs << rhs.getName();

    if (rhs.hasTelephoneNumber()) {
        if (rhs.hasName())
            lhs << std::endl;

        lhs << rhs.getTelephoneNumber();
    }

    return lhs;
}

Contact & Contact::setName(const Character * name) {
    if (name != CONTACTS_NULL) {
        if (!hasName())
            this->name = new Character[CONTACTS_MAX_NAME_LENGTH + 1];

        copy(name, this->name, CONTACTS_MAX_NAME_LENGTH);
    }
    else if (hasName()) {
        delete[] this->name;

        this->name = CONTACTS_NULL;
    }

    return *this;
}
Contact & Contact::setTelephoneNumber(const Character * telephoneNumber) {
    if (telephoneNumber != CONTACTS_NULL) {
        if (!hasTelephoneNumber())
            this->telephoneNumber = new Character[CONTACTS_MAX_TELEPHONE_LENGTH + 1];

        copy(telephoneNumber, this->telephoneNumber, CONTACTS_MAX_TELEPHONE_LENGTH);
    }
    else if (hasTelephoneNumber()) {
        delete[] this->telephoneNumber;

        this->telephoneNumber = CONTACTS_NULL;
    }

    return *this;
}
const Character * Contact::getName() const {
    return name;
}
const Character * Contact::getTelephoneNumber() const {
    return telephoneNumber;
}
Character * Contact::getName() {
    return name;
}
Character * Contact::getTelephoneNumber() {
    return telephoneNumber;
}

Bool Contact::hasName() const {
    return name != CONTACTS_NULL;
}
Bool Contact::hasTelephoneNumber() const {
    return telephoneNumber != CONTACTS_NULL;
}
Bool Contact::isValid() const {
    if (!hasName() || !hasTelephoneNumber())
        return false;

    Character * c = &telephoneNumber[0];

    if (*c != '+' && !std::isdigit(*c))
        return false;

    c++;

    while (*c != '\0') {
        if (!isdigit(*c++))
            return false;
    }

    return true;
}
Int Contact::compare(const Contact & contact) const {
    return contacts::compare(name, contact.getName());
}
Int Contact::compare(const Character * name) const {
    return contacts::compare(this->name, name);
}
Contact & Contact::clear() {
    deallocate();

    return *this;
}

Contact & Contact::allocate(const Character * name, const Character * telephoneNumber) {
    if (name != CONTACTS_NULL) {
        this->name = new Character[CONTACTS_MAX_NAME_LENGTH + 1];
        copy(name, this->name, CONTACTS_MAX_NAME_LENGTH);
    }
    else
        this->name = CONTACTS_NULL;

    if (telephoneNumber != CONTACTS_NULL) {
        this->telephoneNumber = new Character[CONTACTS_MAX_TELEPHONE_LENGTH + 1];
        copy(telephoneNumber, this->telephoneNumber, CONTACTS_MAX_TELEPHONE_LENGTH);
    }
    else
        this->telephoneNumber = CONTACTS_NULL;

    return *this;
}
Contact & Contact::deallocate() {
    if (name != CONTACTS_NULL) {
        delete[] name;

        name = CONTACTS_NULL;
    }

    if (telephoneNumber != CONTACTS_NULL) {
        delete[] telephoneNumber;

        telephoneNumber = CONTACTS_NULL;
    }

    return *this;
}

CONTACTS_NAMESPACE_END