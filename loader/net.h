/*
 * net.h
 *
 * Copyright (C) 2007  Red Hat, Inc.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef H_LOADER_NET
#define H_LOADER_NET

#include <newt.h>
#include "../pyanaconda/isys/iface.h"
#include "loader.h"

#define DHCP_METHOD_STR   _("Dynamic IP configuration (DHCP)")
#define MANUAL_METHOD_STR _("Manual configuration")
#ifdef ENABLE_IPV6
#define DHCPV6_METHOD_STR _("Dynamic IP configuration (DHCPv6)")
#define AUTO_METHOD_STR   _("Automatic neighbor discovery")
#endif

#define SYSCONFIG_PATH       "/etc/sysconfig"
#define NETWORK_SCRIPTS_PATH "/etc/sysconfig/network-scripts"

struct intfconfig_s {
    newtComponent ipv4Entry, cidr4Entry;
    newtComponent gwEntry, nsEntry;
    const char *ipv4, *cidr4;
#ifdef ENABLE_IPV6
    newtComponent ipv6Entry, cidr6Entry;
    const char *ipv6, *cidr6;
    const char *gw6;
#endif
    const char *gw, *ns;
};

struct netconfopts {
    char ipv4Choice;
    int v4Method;
#ifdef ENABLE_IPV6
    char ipv6Choice;
    int v6Method;
#endif
};

typedef int int32;

int readNetConfig(char * device, iface_t * iface,
                  char * dhcpclass, int methodNum);
int configureTCPIP(char * device, iface_t * iface, struct netconfopts * opts,
                   int methodNum);
int manualNetConfig(char * device, iface_t * iface,
                    struct intfconfig_s * ipcomps, struct netconfopts * opts);
void debugNetworkInfo(iface_t * iface);
int writeDisabledNetInfo(void);
int writeDisabledIfcfgFile(char *device);
int removeDhclientConfFile(char *device);
int removeIfcfgFile(char *device);
int writeEnabledNetInfo(iface_t * iface);
int chooseNetworkInterface(struct loaderData_s * loaderData);
void setupIfaceStruct(iface_t * iface, struct loaderData_s * loaderData);
int setupWireless(iface_t * iface);
int kickstartNetworkUp(struct loaderData_s * loaderData,
                       iface_t * iface);
int activateDevice(struct loaderData_s * loaderData,
                   iface_t * iface);
int disconnectDevice(char *device);
void splitHostname (char *str, char **host, char **port);
int wait_for_iface_activation(char * ifname);
int wait_for_iface_disconnection(char *ifname);
int isURLRemote(char *url);
int isValidIPv4Address(const char *address);
int add_and_activate_wifi_connection (char **iface, char *ssid,
				      int protection, char *password,
				      int ip_method_manual, char *address,
                                      char *gateway, char *dns,
                                      char *netmask);
int checkIPsettings (int *ip_info_set, char **ip, char **gateway,
                     char **netmask);
#ifdef ENABLE_IPV6
int isValidIPv6Address(const char *address);
#endif

#endif

#define WIFI_PROTECTION_UNPROTECTED 0
#define WIFI_PROTECTION_WEP 1
#define WIFI_PROTECTION_WPA 2

#define WIFI_ACTIVATION_OK 0
#define WIFI_ACTIVATION_DBUS_ERROR 1
#define WIFI_ACTIVATION_NM_CLIENT_ERROR 2
#define WIFI_ACTIVATION_WIFI_HW_DISABLED 3
#define WIFI_ACTIVATION_BAD_SSID 4
#define WIFI_ACTIVATION_CANNOT_FIND_AP 5
#define WIFI_ACTIVATION_TIMED_OUT 6