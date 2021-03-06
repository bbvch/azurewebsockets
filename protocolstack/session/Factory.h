/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+ or LGPL-3.0+
 */

#ifndef SESSION_FACTORY_H
#define SESSION_FACTORY_H

#include <protocolstack/session/Session.h>

namespace session
{

Session* produce();

}

#endif
