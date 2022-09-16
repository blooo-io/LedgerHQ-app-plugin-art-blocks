#include "art_blocks_plugin.h"

static void handle_address_to(ethPluginProvideParameter_t *msg, artblock_parameters_t *context) {
    memset(context->address_to, 0, sizeof(context->address_to));
    memcpy(context->address_to, &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH], ADDRESS_LENGTH);
    printf_hex_array("Address To: ", ADDRESS_LENGTH, context->address_to);
}

static void handle_purchase_to(ethPluginProvideParameter_t *msg, artblock_parameters_t *context) {
    switch (context->next_param) {
        case ADDRESS_TO:
            handle_address_to(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    artblock_parameters_t *context = (artblock_parameters_t *) msg->pluginContext;

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case PURCHASE:
            break;
        case PURCHASE_TO:
            handle_purchase_to(msg, context);
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
