progname=List
utest=utest_$(progname)
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++03 -I.

debug:   CXXFLAGS+=-g3
release: CXXFLAGS+=-g0 -DNDEBUG

SOURCES:=main.cpp $(wildcard sources/*.cpp)
PREPROCS:=$(patsubst %.cpp,%.ii,$(SOURCES))
DEPENDS:=$(patsubst %.cpp,%.d,$(SOURCES))
ASSEMBLES:=$(patsubst %.cpp,%.s,$(SOURCES))
OBJS:=$(patsubst %.cpp,%.o,$(SOURCES))

UTEST_SOURCES:=main_utest.cpp $(wildcard sources/*.cpp)
UTEST_PREPROCS:=$(patsubst %.cpp,%.ii,$(UTEST_SOURCES))
UTEST_DEPENDS:=$(patsubst %.cpp,%.d,$(UTEST_SOURCES))
UTEST_ASSEMBLES:=$(patsubst %.cpp,%.s,$(UTEST_SOURCES))
UTEST_OBJS:=$(patsubst %.cpp,%.o,$(UTEST_SOURCES))

TEST_INPUTS:=$(wildcard tests/test*.input)
TESTS:=$(patsubst %.input,%,$(TEST_INPUTS))

debug:   qa utest
release: qa

utest: $(utest)
	./$<
	
qa: $(TESTS)

$(TESTS): $(progname)
	./$(progname) < $@.input > $@.output || echo "Negative test..."
	diff $@.output $@.expected > /dev/null && echo "$@ PASSED" || echo "$@ FAILED"
		
$(utest): $(UTEST_OBJS) | .gitignore
	$(CXX) $(CXXFLAGS) $^ -lgtest -lpthread -o $@

$(progname): $(OBJS) | .gitignore
	$(CXX) $(CXXFLAGS) $^ -o $@

%.ii: %.cpp
	$(CXX) $(CXXFLAGS) -E $< -o $@
	$(CXX) $(CXXFLAGS) -MM $< -MT $@ > $(patsubst %.ii,%.d,$@)

%.s: %.ii
	$(CXX) $(CXXFLAGS) -S $< -o $@

%.o: %.s
	$(CXX) $(CXXFLAGS) -c $< -o $@

.gitignore:
	echo $(progname) > .gitignore
	echo $(utest)   >> .gitignore
	
clean:
	rm -rf *.ii *.d *.s *.o sources/*.ii sources/*.d sources/*.s sources/*.o *.output .gitignore $(progname) $(utest)

.PRECIOUS:  $(PREPROCS) $(ASSEMBLES) $(UTEST_PREPROCS) $(UTEST_ASSEMBLES)
.SECONDARY: $(PREPROCS) $(ASSEMBLES) $(UTEST_PREPROCS) $(UTEST_ASSEMBLES)

sinclude $(DEPENDS) $(UTEST_DEPENDS)
