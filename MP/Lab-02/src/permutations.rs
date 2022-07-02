use std::vec;

use crate::combinations::{CombiGen, CombiRegime};

pub enum PermRegime {
    FULL,
    PARTLY(usize),
}

pub struct PermGen<'a, T> {
    set: &'a Vec<T>,
    n: usize,
    i: usize,
    mask: Vec<usize>,
    indexes: Vec<usize>,
    is_init: bool,
    is_over: bool,
    rg: PermRegime,
    combi_gen: Option<CombiGen<'a, T>>,
}

impl<'a, T> PermGen<'a, T> {
    pub fn new(set: &'a Vec<T>) -> Self {
        let len = set.len();
        PermGen {
            set,
            n: len,
            i: 1,
            mask: vec![0; len],
            indexes: (0..len).collect(),
            is_init: false,
            is_over: false,
            rg: PermRegime::FULL,
            combi_gen: None,
        }
    }

    pub fn change_regime(&mut self, new_regime: PermRegime) {
        match new_regime {
            PermRegime::PARTLY(n) if n == self.n => {
                self.rg = PermRegime::FULL;
            }
            _ => self.rg = new_regime,
        }
        self.reset();
    }

    pub fn get_first(&mut self) -> Option<Vec<&T>> {
        if self.is_init || self.is_over {
            return None;
        }
        self.is_init = true;
        if self.n == 1 {
            self.is_over = true;
        }
        match self.rg {
            PermRegime::FULL => {
                return Some(self.set.iter().collect());
            }
            PermRegime::PARTLY(_) => {
                if let Some(first) = self.combi_gen.as_mut().unwrap().get_first() {
                    Some(first)
                } else {
                    self.is_over = true;
                    None
                }
            }
        }
    }

    pub fn get_next(&mut self) -> Option<Vec<&T>> {
        if !self.is_init || self.is_over {
            return None;
        }

        let mut flag = false;

        match self.rg {
            PermRegime::FULL => {
                loop {
                    if self.mask[self.i] < self.i {
                        if self.i % 2 == 0 {
                            self.indexes.swap(0, self.i);
                        } else {
                            self.indexes.swap(self.mask[self.i], self.i);
                        }
                        self.mask[self.i] = self.mask[self.i].saturating_add(1);
                        self.i = 1;
                        flag = true;
                    } else {
                        self.mask[self.i] = 0;
                        self.i = self.i.saturating_add(1);
                    }
                    if !flag && self.i < self.n {
                        continue;
                    }
                    break;
                }
                return if flag {
                    Some(self.indexes.iter().map(|i| &self.set[*i]).collect())
                } else {
                    self.is_over = true;
                    None
                };
            }
            PermRegime::PARTLY(np) => {
                loop {
                    if np == 1 {
                        break;
                    }
                    if self.mask[self.i] < self.i {
                        if self.i % 2 == 0 {
                            self.indexes.swap(0, self.i);
                        } else {
                            self.indexes.swap(self.mask[self.i], self.i);
                        }
                        self.mask[self.i] = self.mask[self.i].saturating_add(1);
                        self.i = 1;
                        flag = true;
                    } else {
                        self.mask[self.i] = 0;
                        self.i = self.i.saturating_add(1);
                    }
                    if !flag && self.i < np {
                        continue;
                    }
                    break;
                }
                return if flag {
                    let curr = self.combi_gen.as_ref().unwrap().get_current().unwrap();
                    Some(self.indexes.iter().map(|i| curr[*i]).collect())
                } else if let Some(next) = self.combi_gen.as_mut().unwrap().get_next() {
                    self.indexes = (0..np).collect();
                    self.mask = vec![0; np];
                    self.i = 1;
                    Some(next)
                } else {
                    None
                };
            }
        }
    }

    pub fn reset(&mut self) {
        self.is_init = false;
        self.is_over = false;
        self.i = 1;
        match self.rg {
            PermRegime::FULL => {
                self.indexes = (0..self.n).collect();
                self.mask = vec![0; self.n];
                self.combi_gen = None;
            }
            PermRegime::PARTLY(np) => {
                self.indexes = (0..np).collect();
                self.mask = vec![0; np];
                self.combi_gen = Some(CombiGen::new(self.set));
                self.combi_gen
                    .as_mut()
                    .unwrap()
                    .change_regime(CombiRegime::PARTLY(np));
            }
        }
    }

    pub fn count(&self) -> usize {
        match (&self.rg, self.n) {
            (_, 0 | 1) => 1,
            (PermRegime::FULL, n) => (1..=n).product(),
            (PermRegime::PARTLY(np), n) => (1..=n)
                .product::<usize>()
                .saturating_div((1..=(n - np)).product()),
        }
    }
}
