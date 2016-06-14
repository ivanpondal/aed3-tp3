#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

template <typename IN>
class experiment{
	public:
		virtual void run(IN &input) = 0;
};

#endif // EXPERIMENT_H_INCLUDED
