#ifndef INCREMENTAL_EXPERIMENT_INPUT_FLOAT_H_
#define INCREMENTAL_EXPERIMENT_INPUT_FLOAT_H_

template <typename S>
class incremental_experiment_input_float: public incremental_experiment_input<float, S>{
	public:
		incremental_experiment_input_float(float min_val, float max_val,
		                                    int discard_val, int repetitions_val, int samples_val,
		                                    const S &subject_val, const char *exp_name):
		                                    incremental_experiment_input<float, S>(min_val, max_val,
		                                    discard_val, repetitions_val, samples_val, subject_val, exp_name){
		}

		~incremental_experiment_input_float(){};

		incremental_experiment_input<float, S> *clone() const{
			return new incremental_experiment_input_float<S>(*this);
		}
	private:
		float calculate_delta() const{
			return (this->get_max() - this->get_min()) / this->get_samples();
		}
};

#endif // INCREMENTAL_EXPERIMENT_INPUT_FLOAT_H_INCLUDED
