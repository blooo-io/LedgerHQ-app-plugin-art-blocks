import { processTest, populateTransaction } from "./test.fixture";

const contractName = "NFTExample";

const testLabel = "Mint"; // <= Name of the test
const testDirSuffix = "mint"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork= "ethereum";

const contractAddr = "0xd7aff4db67e1aa519807221a09c83ade09833992";
const chainID = 1;

const selector = "0x1249c58b";

const inputData = selector;
const value = "12.0";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);


populateTransaction
const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 4, // <= Define the number of steps for this test case and this device
  },

];

devices.forEach((device) =>{
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});