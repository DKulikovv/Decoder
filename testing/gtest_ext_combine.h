#include <gtest/gtest.h>

namespace google_combine
{
    template<typename T, typename G>
    class FromTupleGenerator : public ::testing::internal::ParamGeneratorInterface<T>
    {
        using base_generator_type = ::testing::internal::ParamGeneratorInterface<T>;
        using value_type = T;
        using inner_generator_type = G;
        using inner_iterator_type = decltype(std::declval<inner_generator_type>().begin());
        using base_iterator_type = ::testing::internal::ParamIteratorInterface<T>;

        inner_generator_type gen;

        class Iterator : public base_iterator_type
        {
            const base_generator_type * const base_;
            inner_iterator_type iterator_;
            mutable std::shared_ptr<const T> value_;

            Iterator(const Iterator & other) : base_iterator_type(), base_(other.base_), iterator_(other.iterator_) {}
        public:
            explicit Iterator(const base_generator_type * base, inner_iterator_type it) : base_(base), iterator_(it) {}
            const base_generator_type * BaseGenerator() const override { return base_; }
            void Advance() override { ++iterator_; value_.reset(); }
            base_iterator_type * Clone() const override { return new Iterator(*this); }
            const value_type * Current() const override
            {
                if (value_.get() == NULL) { value_.reset(new value_type(value_type::fromTuple(*iterator_))); }
                return value_.get();
            }
            bool Equals(const base_iterator_type & other) const override
            {
                GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
                    << "The program attempted to compare iterators "
                    << "from different generators." << std::endl;
                return ::testing::internal::CheckedDowncastToActualType<const Iterator>(&other)->iterator_ == iterator_;
            }
        };

    public:
        explicit FromTupleGenerator(const inner_generator_type & g) : gen(g) {}
        FromTupleGenerator & operator = (const FromTupleGenerator &) = delete;
        base_iterator_type * Begin() const override { return new Iterator(this, gen.begin()); }
        base_iterator_type * End() const override { return new Iterator(this, gen.end());
        }
    };

    template<class G>
    struct FromTuplePromoter
    {
        template <class F> struct TupleDetector;
        template <class T, class... Args> struct TupleDetector<T(::testing::tuple<Args...>)> { using type = ::testing::tuple<Args...>; };
        template <class T, class... Args> struct TupleDetector<T(const ::testing::tuple<Args...> &)> { using type = ::testing::tuple<Args...>; };

        G gen;
        FromTuplePromoter(const G & g) : gen(g) {}
        FromTuplePromoter(G && g) : gen(std::move(g)) {}

        template<class T, class U = decltype(T::fromTuple), class V = decltype(static_cast<::testing::internal::ParamGenerator<typename TupleDetector<U>::type>>(std::declval<G>()))>
        operator ::testing::internal::ParamGenerator<T>() const
        {
            return ::testing::internal::ParamGenerator<T>(new FromTupleGenerator<T,V>(gen));
        }
    };

    template <class G>
    FromTuplePromoter<G> fromTuple(G && g)
    {
        return FromTuplePromoter<G>(std::forward<G>(g));
    }
}
