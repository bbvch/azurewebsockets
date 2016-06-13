/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+ or LGPL-3.0+
 */

#include <protocolstack/session/Factory.h>

#include "AzureAmqpWs.h"


namespace session
{

Session *produce()
{
  return new AzureAmqpWs();
}

}
