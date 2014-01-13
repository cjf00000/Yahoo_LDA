/*******************************************************************************
    Copyright (c) 2011 Yahoo! Inc. All rights reserved.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License. See accompanying LICENSE file.

    The Initial Developer of the Original Code is Shravan Narayanamurthy.
******************************************************************************/
/*
 * constants.h
 *
 *  Created on: 24 Mar, 2009
 *      
 */
#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include "types.h"

//The Current Version of Code. Dump files and other
//configs will have to be consistent with this version
//for their use
static const double CURRENT_VERSION = 1.1;

//Num of tokens in flight which is specified for TBB
static const size_t NUM_SAMPLERS = 50000;

//Used to do upfront memory reservation for the updates vector
//which is the vehicle used to transport msgs from the sampler
//to the updater
static const size_t EXP_NUM_WORDS_PER_DOC = 1000;

static const size_t BITS_PER_BYTE = 8;

//Max size permitted for the protobuffer msg
//msgs are written as binary files in (size, msg)* format
static const size_int MAX_MSG_SIZE = 10000000;

//Interval for logging a status msg to INFO
static const int PRT_CNT_INTERVAL = 50000;

//Default value of alphabar
static const double ALPHA_SUM = 50.;

//Default value for beta
static const double BETA = 0.01;

//Default value for gamma
static const double GAMMA = 0.01;

//Default value for delta
static const double DELTA = 0.01;

//when alpha optimization is turned on, alphas
//are always >= MIN_ALPHA
static const double MIN_ALPHA = 0.01;

static const word_t NUM_WORDS_PER_TOP = 20;

static const word_t NUM_TOPICS_PER_DOC = 10;

static const word_t MAX_MSGS = 10;

//The number of Random Number Generators(RNGs)
//used to simulate one RNG per thread behaviour
//as TBB does not allow thread local state. We
//create NUM_RNGS RNGs and access one of them
//pseudo-randomly
static const uint16_t NUM_RNGS = 32;

//Used as the mask instead of mod operator
static const uint16_t RNG_MASK = (1 << 5) - 1;

//Max allowed memory size. If you try allocating
//more than this we will abort
static const uint64_t MAX_MEMORY_USAGE = ((uint64_t) 1) << 34;

//If you try allocating more than this much memory,
//you will be warned that there might be something
//going wrong. If you are using a very large data set
//this is expected
static const uint32_t WARN_MEMORY_SIZE = 1 << 31;

//Max number of attempts before we give up on
//acquiring a lock. This is relevant for the
//multi-machine code
static const uint16_t LOCK_MAX_TRIES = 60;

//This is the maximum number of attempts before
//we give up on waiting for all clients to init.
//This is relevant for the multi-machine code
static const uint16_t INIT_COM_MAX_TRIES = 60;

//Expiry time in secs for the lock set on memcached
//This is relevant for the multi-machine code
static const time_t LOCK_EXPIRY_TIME = 10; //in secs

//This is a multiplier used with the LOCK_EXPIRY_TIME
//when we try to reacquire a lock
//This is relevant for the multi-machine code
static const uint16_t REACQUIRE_BUFFER = 2;

//List of stop words. These will be ignored in the input
static const std::string stopwords[] = { "youwillnevermatchthis" };

//The size of the above list
static const uint16_t NUM_STP_WRDS = sizeof(stopwords) / sizeof(stopwords[0]);

#endif /* CONSTANTS_H_ */
