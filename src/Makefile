SHELL   = /bin/bash
PROJECT := $(realpath $(dir $(lastword $(MAKEFILE_LIST)))/..)
BIN     = $(PROJECT)/bin
SRC     = $(PROJECT)/src
COMMONS = $(SRC)/commons
UNIGRAM = $(SRC)/Unigram_Model

# third party is built from https://github.com/xunzheng/toolkit.git
THIRD_PARTY         = $(HOME)/code/toolkit/third_party
THIRD_PARTY_BIN     = $(THIRD_PARTY)/bin
THIRD_PARTY_LIB     = $(THIRD_PARTY)/lib
THIRD_PARTY_INCLUDE = $(THIRD_PARTY)/include

NEED_MKDIR         = $(BIN)
FORMATTER          = $(BIN)/formatter
LEARNTOPICS        = $(BIN)/learntopics
DM_SERVER          = $(BIN)/DM_Server
MERGE_DICTIONARIES = $(BIN)/Merge_Dictionaries
MERGE_TOPIC_COUNTS = $(BIN)/Merge_Topic_Counts

CXX      = g++
CXXFLAGS = -O4 \
           -std=c++11 \
           -Wall \
           -Wno-strict-aliasing \
	   -fno-builtin-malloc \
           -fno-builtin-calloc \
           -fno-builtin-realloc \
	   -fno-builtin-free \
           -fno-omit-frame-pointer
INCFLAGS = -I$(SRC) \
           -I$(COMMONS) \
           -I$(COMMONS)/Server \
           -I$(UNIGRAM) \
           -I$(THIRD_PARTY_INCLUDE)
LDFLAGS  = -Wl,-rpath,$(THIRD_PARTY_LIB) \
           -L$(THIRD_PARTY_LIB) \
           -pthread \
           -lgflags \
           -lglog \
           -lprotobuf \
           -ltcmalloc \
           -ltbb \
           -lIce \
           -lIceUtil

# ============= objects and dependencies =============

ALL = $(shell find $(SRC) -type f -name '*.cc')
OBJ = $(ALL:.cc=.o)
DEP = $(ALL:.cc=.d)

COMMONS_SRC = $(shell find $(COMMONS) -maxdepth 1 -type f -name '*.cc')
COMMONS_OBJ = $(COMMONS_SRC:.cc=.o)
ifeq (,$(findstring $(COMMONS)/document.pb.o,$(COMMONS_OBJ)))
  COMMONS_OBJ += $(COMMONS)/document.pb.o
endif

COMMONS_FORMATTER_SRC = $(shell find $(COMMONS)/Formatter -type f -name '*.cc')
UNIGRAM_FORMATTER_SRC = $(shell find $(UNIGRAM)/Formatter -type f -name '*.cc')
COMMONS_FORMATTER_OBJ = $(COMMONS_FORMATTER_SRC:.cc=.o)
UNIGRAM_FORMATTER_OBJ = $(UNIGRAM_FORMATTER_SRC:.cc=.o)

TOPICLEARNER_SRC = $(shell find $(COMMONS)/TopicLearner \
                                $(UNIGRAM)/TopicLearner -type f -name '*.cc')
TOPICLEARNER_OBJ = $(TOPICLEARNER_SRC:.cc=.o)

SERVER_SRC = $(shell find $(COMMONS)/Server \
                          $(UNIGRAM)/Server -type f -name '*.cc')
SERVER_OBJ = $(SERVER_SRC:.cc=.o)
ifeq (,$(findstring $(COMMONS)/Server/DistributedMap.o,$(SERVER_OBJ)))
  SERVER_OBJ += $(COMMONS)/Server/DistributedMap.o
endif

# ================= principal rules ==================

all: formatter \
     learntopics \
     dm_server \
     merge_dictionaries \
     merge_topic_counts

-include $(DEP)

path:                    $(NEED_MKDIR)
gensource:               $(COMMONS)/document.pb.h \
                         $(COMMONS)/Server/DistributedMap.h
formatter:          path gensource $(FORMATTER)
learntopics:        path gensource $(LEARNTOPICS)
dm_server:          path gensource $(DM_SERVER)
merge_dictionaries: path gensource $(MERGE_DICTIONARIES)
merge_topic_counts: path gensource $(MERGE_TOPIC_COUNTS)

$(NEED_MKDIR):
	mkdir -p $@

$(FORMATTER):          $(COMMONS_OBJ) \
                       $(COMMONS_FORMATTER_OBJ) \
                       $(UNIGRAM_FORMATTER_OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(LEARNTOPICS):        $(COMMONS_OBJ) \
                       $(TOPICLEARNER_OBJ) \
                       $(UNIGRAM_FORMATTER_OBJ) \
                       $(COMMONS)/Server/DistributedMap.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(DM_SERVER):          $(COMMONS_OBJ) \
                       $(SERVER_OBJ) \
                       $(UNIGRAM)/TopicLearner/TopicCounts.o \
                       $(UNIGRAM)/TopicLearner/eff_small_map.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(MERGE_DICTIONARIES): $(COMMONS_OBJ) \
                       $(UNIGRAM)/Merge/Merge_Dictionaries.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(MERGE_TOPIC_COUNTS): $(COMMONS_OBJ) \
                       $(COMMONS)/Server/DistributedMap.o \
                       $(COMMONS)/TopicLearner/DM_Client.o \
                       $(UNIGRAM)/TopicLearner/TopKList.o \
                       $(UNIGRAM)/TopicLearner/TypeTopicCounts.o \
                       $(UNIGRAM)/TopicLearner/TopicCounts.o \
                       $(UNIGRAM)/TopicLearner/eff_small_map.o \
                       $(UNIGRAM)/Merge/Merge_Topic_Counts.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

%.o: %.cc
	$(CXX) -c -MMD -MP $(CXXFLAGS) $(INCFLAGS) $< -o $@

$(COMMONS)/%.pb.cc $(COMMONS)/%.pb.h: $(SRC)/%.proto
	$(THIRD_PARTY_BIN)/protoc -I=$(SRC) --cpp_out=$(COMMONS) $<

%/DistributedMap.cc %/DistributedMap.h: %/DistributedMap.ice
	$(THIRD_PARTY_BIN)/slice2cpp --output-dir $* $<
	mv $*/DistributedMap.{cpp,cc}

clean:
	@rm -rf $(BIN) \
                $(OBJ) \
                $(DEP) \
                $(COMMONS)/document.pb.{h,cc,d,o} \
                $(COMMONS)/Server/DistributedMap.{h,cc,d,o}

.PHONY: all \
        path \
        gensource \
        formatter \
        learntopics \
        dm_server \
        merge_dictionaries \
        merge_topic_counts \
        clean

