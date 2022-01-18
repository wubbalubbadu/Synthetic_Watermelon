#include "model.hxx"
#include <catch.hxx>
#include "fruit.hxx"
#include <vector>
using namespace ge211;


TEST_CASE("merge w/o reposition")
{
    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({100,100},true,2));
    set.add_fruits(fruit({120,120},true,2));
    set.merge();
    CHECK(set.get_fruits()->at(0) == fruit({110,110},true,3));
}

TEST_CASE("merge and repositioning when touching LEFT side")
{
    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({10,100},true,2));
    set.add_fruits(fruit({20,120},true,2));
    set.merge();
    CHECK(set.get_fruits()->at(0) == fruit({55,110},true,3));
}

TEST_CASE("merge and repositioning when touching RIGHT side")
{
    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({600,100},true,2));
    set.add_fruits(fruit({600,120},true,2));
    set.merge();
    CHECK(set.get_fruits()->at(0) == fruit({544,110},true,3));
}

TEST_CASE("all_overlap: returns the height of the highest circle that is "
          "overlapping "
          "with the vector")
{
    Model model;
    fruit a = fruit({55,110},true,3);
    fruit b = fruit({400,400},true,3);
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({65,110},true,2));
    set.add_fruits(fruit({500,120},true,2));
    CHECK(set.all_overlapped(a) == 110);
    CHECK(set.all_overlapped(b) == 0);
}

TEST_CASE("float check")
{

    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({500,120},false,2));
    set.add_fruits(fruit({65,110},false,2));
    set.add_fruits(fruit({56,120},false,3));
    set.float_check();
    //not overlapping: false -> true
    CHECK(set.get_fruits()->at(0).get_live());

    //overlaps but at the bottom
    //upper: false -> false
    CHECK_FALSE(set.get_fruits()->at(1).get_live());
    //lower: false -> true
    CHECK(set.get_fruits()->at(2).get_live());

    //touches edge: false -> false
    set.add_fruits(fruit({0,50},false,2));
    set.add_fruits(fruit({599,50},false,2));
    set.add_fruits(fruit({200,799},false,2));
    set.add_fruits(fruit({0,799},false,2));
    set.float_check();
    CHECK_FALSE(set.get_fruits()->at(3).get_live());
    CHECK_FALSE(set.get_fruits()->at(4).get_live());
    CHECK_FALSE(set.get_fruits()->at(5).get_live());
    CHECK_FALSE(set.get_fruits()->at(6).get_live());


}

//
// These tests should demonstrate at least six of the functional
// requirements.
//
