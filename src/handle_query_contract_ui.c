#include "art_blocks_plugin.h"

// Set UI for "Amount" screen.
static void set_amount_ui(ethQueryContractUI_t *msg, artblock_parameters_t *context) {
    strlcpy(msg->title, "Amount", msg->titleLength);

    // set network ticker (ETH, BNB, etc) if needed
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }

    amountToString(msg->pluginSharedRO->txContent->value.value,
                   msg->pluginSharedRO->txContent->value.length,
                   WEI_TO_ETHER,
                   context->ticker_sent,
                   msg->msg,
                   msg->msgLength);
}

static void set_address_to_ui(ethQueryContractUI_t *msg, artblock_parameters_t *context) {
    strlcpy(msg->title, "To Address", msg->titleLength);

    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    getEthAddressStringFromBinary((uint8_t *) context->address_to,
                                  msg->msg + 2,
                                  msg->pluginSharedRW->sha3,
                                  0);
}

static uint8_t amount_screen(uint8_t index) {
    switch (index) {
        case 0:
            return AMOUNT_SCREEN;
        default:
            return ERROR;
            break;
    }
}

static uint8_t address_to_screen(uint8_t index) {
    switch (index) {
        case 0:
            return AMOUNT_SCREEN;
        case 1:
            return ADDRESS_TO_SCREEN;
        default:
            return ERROR;
            break;
    }
}

// Helper function that returns the enum corresponding to the screen that should be displayed.
static screens_t get_screen(const ethQueryContractUI_t *msg, const artblock_parameters_t *context) {
    uint8_t index = msg->screenIndex;
    switch (context->selectorIndex) {
        case PURCHASE:
            return amount_screen(index);
        case PURCHASE_TO:
            return address_to_screen(index);
    }
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    artblock_parameters_t *context = (artblock_parameters_t *) msg->pluginContext;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);
    msg->result = ETH_PLUGIN_RESULT_OK;

    screens_t screen = get_screen(msg, context);

    switch (screen) {
        case AMOUNT_SCREEN:
            set_amount_ui(msg, context);
            break;
        case ADDRESS_TO_SCREEN:
            set_address_to_ui(msg, context);
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
