//
// Created by Giacomo Bergami on 10/09/16.
//

#include <librdf.h>
#include <rdf_storage.h>
#include <iostream>
#include <rdf_init.h>
#include <rdf_model.h>
#include "Virtuoso.h"

Virtuoso::Virtuoso() : Virtuoso{"db1"} {}

Virtuoso::Virtuoso(char* chare) {
    world=librdf_new_world();
    librdf_world_open(world);
    storage=librdf_new_storage(world, "virtuoso",chare ? chare : "db1","dsn='VOS',user='dba',password='dba'");
    if(!storage) {
        fprintf(stderr, ": Failed to open virtuoso/VOS on db1\n");
        status = STORAGE_FAILURE;
        exit (1);
    }
    model=librdf_new_model(world, storage, NULL);
    if(!model) {
        fprintf(stderr, ": Failed to create model\n");
        status = MODEL_FAILURE;
    }
    status = VIRTUOSO_OK;
}


VirtuosoGraph* Virtuoso::openGraph(std::string& name) {
    Virtuoso* virt = this;
    std::cerr << "ERR: " << name << std::endl;
    VirtuosoGraph* vg = new VirtuosoGraph(virt,name);
    return vg;
}

Virtuoso::~Virtuoso() {
    librdf_free_model(model);
    librdf_free_storage(storage);
    librdf_free_world(world);
}

VirtuosoQuery* Virtuoso::compileQuery(std::string& query) {
    Virtuoso* virt = this;
    return new VirtuosoQuery(virt,query);
}

