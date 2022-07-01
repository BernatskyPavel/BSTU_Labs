pub enum CombiRegime {
    FULL,
    PARTLY(usize),
}

pub struct CombiGen<'a, T> {
    set: &'a Vec<T>,
    n: usize,
    sn: u32,
    mask: usize,
    rg: CombiRegime,
    is_init: bool,
    is_over: bool,
}

impl<'a, T> CombiGen<'a, T> {
    pub fn change_regime(&mut self, new_regime: CombiRegime) {
        self.rg = new_regime;
        self.reset();
    }

    pub fn count(&self) -> usize {
        match self.rg {
            CombiRegime::FULL => 2_usize.pow(self.n as u32),
            CombiRegime::PARTLY(np) => ((self.n.saturating_sub(np - 1))..=self.n)
                .product::<usize>()
                .saturating_div((1..=np).product()),
        }
    }

    pub fn get_first(&mut self) -> Option<Vec<&T>> {
        if self.is_init {
            return None;
        }

        match self.rg {
            CombiRegime::FULL => {
                self.mask += 1;
                self.sn = self.mask.count_ones();
                self.is_init = true;
                Some(vec![])
            }
            CombiRegime::PARTLY(pn) => match pn.partial_cmp(&self.n).unwrap() {
                std::cmp::Ordering::Greater => None,
                std::cmp::Ordering::Equal => {
                    self.is_init = true;
                    self.is_over = true;
                    Some(self.set.iter().collect())
                }
                std::cmp::Ordering::Less => {
                    if let Some(mask) = self.get_next_mask(self.mask, pn as u32) {
                        self.mask = mask;
                    } else {
                        self.is_init = true;
                        self.is_over = true;
                        return None;
                    }
                    self.is_init = true;

                    Some(
                        self.set
                            .iter()
                            .enumerate()
                            .filter(|&(t, _)| (self.mask >> t) & 1 == 1)
                            .map(|(_, element)| element)
                            .collect(),
                    )
                }
            },
        }
    }

    fn get_max_partial_mask(&self) -> usize {
        match self.rg {
            CombiRegime::FULL => 0,
            CombiRegime::PARTLY(pn) => {
                let init_mask = 2_usize.pow(pn as u32);
                init_mask << (self.n - pn)
            }
        }
    }

    pub fn get_next(&mut self) -> Option<Vec<&T>> {
        if !self.is_init || self.is_over {
            return None;
        }

        match self.rg {
            CombiRegime::FULL => {
                let res = Some(
                    self.set
                        .iter()
                        .enumerate()
                        .filter(|&(t, _)| (self.mask >> t) & 1 == 1)
                        .map(|(_, element)| element)
                        .collect(),
                );

                if self.sn as usize == self.n {
                    self.is_over = true;
                }

                self.mask += 1;
                self.sn = self.mask.count_ones();

                res
            }
            CombiRegime::PARTLY(pn) => {
                if let Some(mask) = self.get_next_mask(self.mask, pn as u32) {
                    self.mask = mask;
                } else {
                    self.is_over = true;
                    return None;
                }

                Some(
                    self.set
                        .iter()
                        .enumerate()
                        .filter(|&(t, _)| (self.mask >> t) & 1 == 1)
                        .map(|(_, element)| element)
                        .collect(),
                )
            }
        }
    }

    fn get_next_mask(&self, mask: usize, pn: u32) -> Option<usize> {
        if pn == 0 {
            return None;
        }

        let mut next_mask = mask;
        loop {
            next_mask = next_mask.saturating_add(1);
            if next_mask.count_ones() == pn {
                break;
            }
        }
        if next_mask < self.get_max_partial_mask() {
            Some(next_mask)
        } else {
            None
        }
    }

    pub fn get_current(&self) -> Option<Vec<&T>> {
        if !self.is_init {
            None
        } else {
            Some(
                self.set
                    .iter()
                    .enumerate()
                    .filter(|&(t, _)| (self.mask >> t) & 1 == 1)
                    .map(|(_, element)| element)
                    .collect(),
            )
        }
    }

    pub fn new(set: &'a Vec<T>) -> Self {
        CombiGen {
            n: set.len(),
            set,
            sn: 0,
            mask: 0,
            rg: CombiRegime::FULL,
            is_init: false,
            is_over: false,
        }
    }

    pub fn reset(&mut self) {
        self.sn = 0;
        self.mask = 0;
        self.is_init = false;
        self.is_over = false;
    }
}
