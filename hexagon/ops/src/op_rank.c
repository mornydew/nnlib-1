/*
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 *    * Neither the name of The Linux Foundation nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 * GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <nn_graph.h>
#include <string.h>
#include <quantize.h>
#include <math.h>

static int rank_execute(struct nn_node *self, struct nn_graph *nn)
{
	//const struct tensor *in_tensor = self->inputs[0];
	const struct tensor *true_rank_tensor = self->inputs[1];
	struct tensor *out_tensor = self->outputs[0];
	size_t bytes = sizeof(int32_t);
	int rank = tensor_get_int32(true_rank_tensor,0);

	logmsg(nn,2,"rank execute. self=%p ",self);

	bytes = 1 * sizeof(int32_t);
	if (bytes > out_tensor->max_size) return errlog(nn,"out too small");
	tensor_set_shape(out_tensor,1,1,1,1);
	out_tensor->data_size = bytes;

	tensor_set_int32(out_tensor,0,rank);

	logmsg(nn,2,"rank %p done",self);
	return 0;
}

static int rank_check(struct nn_node *self, struct nn_graph *nn)
{
	logmsg(nn,2,"Checking rank node %p",self);
	if (self->n_inputs != 2) return errlog(nn,"wrong # inputs");
	if (self->n_outputs != 1) return errlog(nn,"wrong # outputs");
	logmsg(nn,2,"range rank %p check OK",self);
	return 0;
}

struct nn_node_ops nn_ops_for_Rank_int32 = {
	.execute = rank_execute,
	.check = rank_check,
	.ctor = node_alloc_common,
	.dtor = node_free_common,
};

