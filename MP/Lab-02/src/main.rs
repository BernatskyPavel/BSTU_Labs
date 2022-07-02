pub mod boat;
pub mod combinations;
pub mod knapsack;
pub mod permutations;
pub mod salesman;

fn main() {
    salesman::measure_salesman();
    knapsack::measure_knapsack();
    boat::measure_boat();
    boat::measure_boat_c();
}
