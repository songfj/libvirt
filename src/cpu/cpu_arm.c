/*
 * cpu_arm.c: CPU driver for arm CPUs
 *
 * Copyright (C) 2013 Red Hat, Inc.
 * Copyright (C) Canonical Ltd. 2012
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Chuck Short <chuck.short@canonical.com>
 */

#include <config.h>

#include "viralloc.h"
#include "cpu.h"

#define VIR_FROM_THIS VIR_FROM_CPU

static const virArch archs[] = { VIR_ARCH_ARMV7L };

static virCPUDataPtr
ArmNodeData(virArch arch)
{
    virCPUDataPtr data;

    if (VIR_ALLOC(data) < 0)
        return NULL;

    data->arch = arch;

    return data;
}

static int
ArmDecode(virCPUDefPtr cpu ATTRIBUTE_UNUSED,
          const virCPUData *data ATTRIBUTE_UNUSED,
          const char **models ATTRIBUTE_UNUSED,
          unsigned int nmodels ATTRIBUTE_UNUSED,
          const char *preferred ATTRIBUTE_UNUSED,
          unsigned int flags)
{

    virCheckFlags(VIR_CONNECT_BASELINE_CPU_EXPAND_FEATURES, -1);

    return 0;
}

static void
ArmDataFree(virCPUDataPtr data)
{
    VIR_FREE(data);
}

struct cpuArchDriver cpuDriverArm = {
    .name = "arm",
    .arch = archs,
    .narch = ARRAY_CARDINALITY(archs),
    .compare = NULL,
    .decode = ArmDecode,
    .encode = NULL,
    .free = ArmDataFree,
    .nodeData = ArmNodeData,
    .guestData = NULL,
    .baseline = NULL,
    .update = NULL,
    .hasFeature = NULL,
};
