#include "art_blocks_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    artblock_parameters_t *context = (artblock_parameters_t *) msg->pluginContext;

    strlcpy(msg->name, "Art Blocks", msg->nameLength);

    switch (context->selectorIndex) {
        case PURCHASE:
            strlcpy(msg->version, "Purchase", msg->versionLength);
            break;
        case PURCHASE_TO:
            strlcpy(msg->version, "Purchase to", msg->versionLength);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}