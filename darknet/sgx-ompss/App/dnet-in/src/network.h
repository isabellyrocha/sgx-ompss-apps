
#ifndef NETWORK_H_IN
#define NETWORK_H_IN
#include "darknet.h"

#include "image.h"
#include "layer.h"
#include "data.h"
#include "tree.h"



void compare_networks(network n1, network n2, data d);
char *get_layer_string(LAYER_TYPE a);

network make_network(int n);

void fuse_conv_batchnorm(network net);
void calculate_binary_weights(network net);
float network_accuracy_multi(network net, data d, int n);
int get_predicted_class_network(network net);
//void print_network(network *net);
//int resize_network(network net, int w, int h);
void calc_network_cost(network net);

#endif

