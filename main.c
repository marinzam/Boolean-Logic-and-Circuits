/*
 * File: main.c
 * Author: Geraldine Marin-Zamora
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.

static Circuit* Circuits_and3() {
    Value* in0 = new_Value(false);
    Value* in1 = new_Value(false);
    Value* in2 = new_Value(false);
    Gate* and0 = new_AndGate(in0, in1);
    Gate* and1 = new_AndGate(Gate_getOutput(and0), in2);

    Value** inputs = new_Value_array(3);
    inputs[0] = in0;
    inputs[1] = in1;
    inputs[2] = in2;
    Value** outputs = new_Value_array(1);
    outputs[0] = Gate_getOutput(and1);
    Gate** gates = new_Gate_array(2);
    gates[0] = and0;
    gates[1] = and1;
    return new_Circuit(3, inputs, 1, outputs, 2, gates);
}
 */

// Circuit Number One: x!y + yz = output
static Circuit* Circuits_Num1() {
    Value* in0 = new_Value(false); // x
    Value* in1 = new_Value(false); // y
    Value* in2 = new_Value(false); // z
    Gate* not0 = new_Inverter(in1); // !y
    Gate* and0 = new_AndGate(in0, Gate_getOutput(not0)); // x!y
    Gate* and1 = new_AndGate(in1, in2); // yz
    Gate* or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1)); // x!y + yz

    Value** inputs = new_Value_array(3);
    inputs[0] = in0;
    inputs[1] = in1;
    inputs[2] = in2;
    Value** outputs = new_Value_array(1);
    outputs[0] = Gate_getOutput(or0);
    Gate** gates = new_Gate_array(4);
    gates[0] = not0;
    gates[1] = and0;
    gates[2] = and1;
    gates[3] = or0;
    return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

// Circuit Number Two: !(!(x!y) + !(yz)) = output
static Circuit* Circuits_Num2() {
    Value* in0 = new_Value(false); // x
    Value* in1 = new_Value(false); // y
    Value* in2 = new_Value(false); // z
    Gate* not0 = new_Inverter(in1); // !y
    Gate* nand0 = new_NandGate(in0, Gate_getOutput(not0)); // !(x!y)
    Gate* nand1 = new_NandGate(in1, in2); // !(yz)
    Gate* nor0 = new_NorGate(Gate_getOutput(nand0), Gate_getOutput(nand1)); // x!y + yz

    Value** inputs = new_Value_array(3);
    inputs[0] = in0;
    inputs[1] = in1;
    inputs[2] = in2;
    Value** outputs = new_Value_array(1);
    outputs[0] = Gate_getOutput(nor0);
    Gate** gates = new_Gate_array(4);
    gates[0] = not0;
    gates[1] = nand0;
    gates[2] = nand1;
    gates[3] = nor0;
    return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

// Circuit testing: NAND
static Circuit* Circuits_NAND() {
    Value* in0 = new_Value(false); // x
    Value* in1 = new_Value(false); // y
    Gate* nand0 = new_NandGate(in0, in1); // !(x!y)

    Value** inputs = new_Value_array(2);
    inputs[0] = in0;
    inputs[1] = in1;
    Value** outputs = new_Value_array(1);
    outputs[0] = Gate_getOutput(nand0);
    Gate** gates = new_Gate_array(1);
    gates[0] = nand0;
    return new_Circuit(2, inputs, 1, outputs, 1, gates);
}

// Circuit testing: NOR
static Circuit* Circuits_NOR() {
    Value* in0 = new_Value(false); // x
    Value* in1 = new_Value(false); // y
    Gate* nor0 = new_NorGate(in0, in1); // !(x!y)

    Value** inputs = new_Value_array(2);
    inputs[0] = in0;
    inputs[1] = in1;
    Value** outputs = new_Value_array(1);
    outputs[0] = Gate_getOutput(nor0);
    Gate** gates = new_Gate_array(1);
    gates[0] = nor0;
    return new_Circuit(2, inputs, 1, outputs, 1, gates);
}

// Circuit Number Three: xy + !x!y = z
static Circuit* Circuits_Num3() {
    Value* in0 = new_Value(false); // x
    Value* in1 = new_Value(false); // y
    Gate* and0 = new_AndGate(in0, in1); // xy
    Gate* not0 = new_Inverter(in0); // !x
    Gate* not1 = new_Inverter(in1); // !y
    Gate* and1 = new_AndGate(Gate_getOutput(not0), Gate_getOutput(not1)); // !x!y
    Gate* or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1)); // xy + !x!y

    Value** inputs = new_Value_array(2);
    inputs[0] = in0;
    inputs[1] = in1;
    Value** z = new_Value_array(1);
    z[0] = Gate_getOutput(or0);
    Gate** gates = new_Gate_array(5);
    gates[0] = and0;
    gates[1] = not0;
    gates[2] = not1;
    gates[3] = and1;
    gates[4] = or0;
    return new_Circuit(2, inputs, 1, z, 5, gates);
}

// Extra credit: 1-bit adder: xy + xc + yc (carry out d)
static Circuit* Circuits_Adder_d() {
    Value* in0 = new_Value(false); // x
    Value* in1 = new_Value(false); // y
    Value* in2 = new_Value(false); // c
    Gate* and0 = new_AndGate(in0, in1); // xy
    Gate* and1 = new_AndGate(in0, in2); // xc
    Gate* and2 = new_AndGate(in1, in2); // yc
    Gate* or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1)); // xy + xc
    Gate* or1 = new_OrGate(Gate_getOutput(or0), Gate_getOutput(and2)); // xy + xc + yc

    Value** inputs = new_Value_array(3);
    inputs[0] = in0;
    inputs[1] = in1;
    inputs[2] = in2;
    Value** outputs = new_Value_array(1);
    outputs[0] = Gate_getOutput(or1);
    Gate** gates = new_Gate_array(5);
    gates[0] = and0;
    gates[1] = and1;
    gates[2] = and2;
    gates[3] = or0;
    gates[4] = or1;
    return new_Circuit(3, inputs, 1, outputs, 5, gates);
}

// Extra credit: 1-bit adder: !x!yc + !xy!c + x!y!c + xyc (output z)
static Circuit* Circuits_Adder_z() {
    Value* in0 = new_Value(false); // x
    Value* in1 = new_Value(false); // y
    Value* in2 = new_Value(false); // c
    Gate* not0 = new_Inverter(in0); // !x
    Gate* not1 = new_Inverter(in1); // !y
    Gate* not2 = new_Inverter(in2); // !c

    Gate* and3_0 = new_And3Gate(Gate_getOutput(not0),
                                Gate_getOutput(not1),
                                in2); // !x!yc

    Gate* and3_1 = new_And3Gate(Gate_getOutput(not0),
                                in1,
                                Gate_getOutput(not2)); // !xy!c

    Gate* and3_2 = new_And3Gate(in0,
                                Gate_getOutput(not1),
                                Gate_getOutput(not2)); // x!y!c

    Gate* and3_3 = new_And3Gate(in0,
                                in1,
                                in2); // !xy!c

    Gate* or4_0 = new_Or4Gate(Gate_getOutput(and3_0),
                            Gate_getOutput(and3_1),
                            Gate_getOutput(and3_2),
                            Gate_getOutput(and3_3));

    Value** inputs = new_Value_array(3);
    inputs[0] = in0;
    inputs[1] = in1;
    inputs[2] = in2;
    Value** outputs = new_Value_array(1);
    outputs[0] = Gate_getOutput(or4_0);
    Gate** gates = new_Gate_array(8);
    gates[0] = not0;
    gates[1] = not1;
    gates[2] = not2;
    gates[3] = and3_0;
    gates[4] = and3_1;
    gates[5] = and3_2;
    gates[6] = and3_3;
    gates[7] = or4_0;
    return new_Circuit(3, inputs, 1, outputs, 8, gates);
}


static char* b2s(bool b) {
    return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_setInput(circuit, 2, in2);
    //Circuit_dump(circuit);
    Circuit_update(circuit);
    bool out0 = Circuit_getOutput(circuit, 0);
    printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

static void test2In1Out(Circuit* circuit, bool in0, bool in1) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    //Circuit_dump(circuit);
    Circuit_update(circuit);
    bool out0 = Circuit_getOutput(circuit, 0);
    printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}


int main(int argc, char **argv) {
    /*
    Circuit* c = Circuits_and3();
    printf("Some input(s) false: should be false\n");
    test3In1Out(c, true, true, false);
    printf("All inputs true: should be true\n");
    test3In1Out(c, true, true, true);
     */

    //test for Circuit 1
    printf("\n\nPrinting Tests for Circuit 1: x!y + yz\n");
    Circuit* c1 = Circuits_Num1();
    printf("x = F, y = F, z = F: should be false\n");
    test3In1Out(c1, false, false, false);
    printf("x = T, y = F, z = F: should be true\n");
    test3In1Out(c1, true, false, false);
    printf("x = F, y = T, z = F: should be false\n");
    test3In1Out(c1, false, true, false);
    printf("x = F, y = F, z = T: should be false\n");
    test3In1Out(c1, false, false, true);
    printf("x = T, y = T, z = F: should be false\n");
    test3In1Out(c1, true, true, false);
    printf("x = T, y = F, z = T: should be true\n");
    test3In1Out(c1, true, false, true);
    printf("x = F, y = T, z = T: should be true\n");
    test3In1Out(c1, false, true, true);
    printf("x = T, y = T, z = T: should be true\n");
    test3In1Out(c1, true, true, true);

    //test for NAND gate
    printf("\n\nPrinting Test for NAND gate:\n");
    Circuit* test1 = Circuits_NAND();
    printf("x = F, y = F: should be true\n");
    test2In1Out(test1, false, false);
    printf("x = T, y = F: should be true\n");
    test2In1Out(test1, true, false);
    printf("x = F, y = T: should be true\n");
    test2In1Out(test1, false, true);
    printf("x = T, y = T: should be false\n");
    test2In1Out(test1, true, true);

    //test for NOR gate
    printf("\n\nPrinting Test for NOR gate:\n");
    Circuit* test2 = Circuits_NOR();
    printf("x = F, y = F: should be true\n");
    test2In1Out(test2, false, false);
    printf("x = T, y = F: should be false\n");
    test2In1Out(test2, true, false);
    printf("x = F, y = T: should be false\n");
    test2In1Out(test2, false, true);
    printf("x = T, y = T: should be false\n");
    test2In1Out(test2, true, true);


    //test for Circuit 2
    printf("\n\nPrinting Tests for Circuit 2: !(!(x!y) + !(yz))\n");
    Circuit* c2 = Circuits_Num2();

    printf("x = F, y = F, z = F: should be false\n");
    test3In1Out(c2, false, false, false);
    printf("x = T, y = F, z = F: should be false\n");
    test3In1Out(c2, true, false, false);
    printf("x = F, y = T, z = F: should be false\n");
    test3In1Out(c2, false, true, false);
    printf("x = F, y = F, z = T: should be false\n");
    test3In1Out(c2, false, false, true);
    printf("x = T, y = T, z = F: should be false\n");
    test3In1Out(c2, true, true, false);
    printf("x = T, y = F, z = T: should be false\n");
    test3In1Out(c2, true, false, true);
    printf("x = F, y = T, z = T: should be false\n");
    test3In1Out(c2, false, true, true);
    printf("x = T, y = T, z = T: should be false\n");
    test3In1Out(c2, true, true, true);

    //test for Circuit 3
    printf("\n\nPrinting Tests for Circuit 3: xy + !x!y\n");
    Circuit* c3 = Circuits_Num3();
    printf("x = F, y = F: should be true\n");
    test2In1Out(c3, false, false);
    printf("x = T, y = F: should be false\n");
    test2In1Out(c3, true, false);
    printf("x = F, y = T: should be false\n");
    test2In1Out(c3, false, true);
    printf("x = T, y = T: should be true\n");
    test2In1Out(c3, true, true);

    printf("\n\n********************************************************\n");
    printf("***** Extra Credit: 1-bit Adder (carry out and sum). ***\n");
    printf("********************************************************\n");


    //test for 1-bit adder (carry out d)
    printf("\n\nPrinting Tests for 1-bit Adder (carry out d): xy + xc + yc = d\n");
    Circuit* carry_out = Circuits_Adder_d();
    printf("x = F, y = F, c = F: should be false\n");
    test3In1Out(carry_out, false, false, false);
    printf("x = T, y = F, c = F: should be false\n");
    test3In1Out(carry_out, true, false, false);
    printf("x = F, y = T, c = F: should be false\n");
    test3In1Out(carry_out, false, true, false);
    printf("x = F, y = F, c = T: should be false\n");
    test3In1Out(carry_out, false, false, true);
    printf("x = T, y = T, c = F: should be true\n");
    test3In1Out(carry_out, true, true, false);
    printf("x = T, y = F, c = T: should be true\n");
    test3In1Out(carry_out, true, false, true);
    printf("x = F, y = T, c = T: should be true\n");
    test3In1Out(carry_out, false, true, true);
    printf("x = T, y = T, c = T: should be true\n");
    test3In1Out(carry_out, true, true, true);

    //test for 1-bit adder (z)
    printf("\n\nPrinting Tests for 1-bit Adder (z): !x!yc + !xy!c + x!y!c + xyc = z\n");
    Circuit* sum = Circuits_Adder_z();
    printf("x = F, y = F, c = F: should be false\n");
    test3In1Out(sum, false, false, false);
    printf("x = T, y = F, c = F: should be true\n");
    test3In1Out(sum, true, false, false);
    printf("x = F, y = T, c = F: should be true\n");
    test3In1Out(sum, false, true, false);
    printf("x = F, y = F, c = T: should be true\n");
    test3In1Out(sum, false, false, true);
    printf("x = T, y = T, c = F: should be false\n");
    test3In1Out(sum, true, true, false);
    printf("x = T, y = F, c = T: should be false\n");
    test3In1Out(sum, true, false, true);
    printf("x = F, y = T, c = T: should be false\n");
    test3In1Out(sum, false, true, true);
    printf("x = T, y = T, c = T: should be true\n");
    test3In1Out(sum, true, true, true);

    printf("\n\nEnd of program.\n");
}
