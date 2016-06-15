#ifndef INCREMENTAL_EXPERIMENT_INPUT_INT_H_
#define INCREMENTAL_EXPERIMENT_INPUT_INT_H_

template <typename S>
class incremental_experiment_input_int: public incremental_experiment_input<int, S>{
	public:
		incremental_experiment_input_int(int min_val, int max_val,
		                                 int discard_val, int repetitions_val, int samples_val, const S &subject_val):
		                                 incremental_experiment_input<int, S>(min_val, max_val,
		                                 discard_val, repetitions_val, samples_val, subject_val){
		}

		~incremental_experiment_input_int(){};

		incremental_experiment_input<int, S> *clone() const{
			return new incremental_experiment_input_int<S>(*this);
		}
	private:
		int calculate_delta() const{
			return (this->get_max() - this->get_min()) / this->get_samples();
		}
};
 
#endif // INCREMENTAL_EXPERIMENT_INPUT_INT_H_INCLUDED
