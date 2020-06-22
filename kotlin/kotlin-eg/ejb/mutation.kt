class mutation {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            /*
    val list: List<String> = listOf("a", "b", "c", "d")
    val mutableList: MutableList<String>? = list as? MutableList<String>
    mutableList?.add("e")
    println(list)
    println(mutableList)
    */
            val fruits = listOf("apple", "banana", "pear")
            // (fruits as MutableList).add("kumquat")
            (fruits as MutableList)[1] = "kumquat"
            println(fruits)
            assert(fruits == listOf("apple", "kumquat", "pear"))
        }
    }
}
