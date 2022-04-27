//
// Created by Benedikt on 26.04.2022.
// Copyright 2022, Laminoid.com (Muessig & Muessig GbR).
// Licensed under the terms and conditions of the GPLv3.
//

#include <stdio.h>
#include <stdlib.h>

#include "libsprintpcb/list.h"
#include "libsprintpcb/primitives.h"
#include "libsprintpcb/elements.h"
#include "libsprintpcb/stringbuilder.h"

int main() {
    sprint_element circle = sprint_circle_create(
            SPRINT_LAYER_MECHANICAL,
            10,
            sprint_tuple_of(10, 20),
            10);

    sprint_stringbuilder* builder = sprint_stringbuilder_of("Circle and builder test:\n");
    sprint_stringbuilder_format(builder, "layer: %d\n", circle.circle.layer);
    sprint_stringbuilder_format(builder, "width: %d\n", circle.circle.width);

    sprint_stringbuilder_format(builder, "center: ");
    sprint_tuple_string(&circle.circle.center, builder);
    sprint_stringbuilder_format(builder, "\n");
    sprint_stringbuilder_format(builder, "radius: %d\n", circle.circle.radius);
    sprint_stringbuilder_format(builder, "(clear): %d\n", circle.circle.clear);
    sprint_stringbuilder_format(builder, "(cutout): %d\n", circle.circle.cutout);
    sprint_stringbuilder_format(builder, "(soldermask): %d\n", circle.circle.soldermask);
    sprint_stringbuilder_format(builder, "(start): %d\n", circle.circle.start);
    sprint_stringbuilder_format(builder, "(stop): %d\n", circle.circle.stop);
    sprint_stringbuilder_format(builder, "(fill): %d\n\n", circle.circle.fill);
    sprint_element_destroy(&circle);

    sprint_stringbuilder_flush(builder, stdout);

    sprint_tuple tuple1, tuple2;
    tuple1.x = 1;
    tuple1.y = 2;
    tuple2.x = 3;
    tuple2.y = 4;

    printf("track %d\n", sizeof(sprint_track));
    printf("pad_tht %d\n", sizeof(sprint_pad_tht));
    printf("pad_smt %d\n", sizeof(sprint_pad_smt));
    printf("zone %d\n", sizeof(sprint_zone));
    printf("text %d\n", sizeof(sprint_text));
    printf("circle %d\n", sizeof(sprint_circle));
    printf("component %d\n", sizeof(sprint_component));
    printf("group %d\n", sizeof(sprint_group));
    printf("\nelement %d\n", sizeof(sprint_element));

    sprint_list* list = sprint_list_create(sizeof(sprint_tuple), 0);
    sprint_list_add(list, &tuple1);
    sprint_list_add(list, &tuple2);
    sprint_list_add(list, &tuple2);

    for (int i = 0; i < list->count; i++) {
        sprint_tuple* tuple = (sprint_tuple*)sprint_list_get(list, i);
        printf("%d / %d\n", tuple->x, tuple->y);
    }

    sprint_list_destroy(list);

    return 0;
}
