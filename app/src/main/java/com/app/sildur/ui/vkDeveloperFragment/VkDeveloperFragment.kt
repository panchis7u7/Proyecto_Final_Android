package com.app.sildur.ui.vkDeveloperFragment

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import com.app.sildur.R
import com.app.sildur.ui.viewModels.VkDeveloperViewModel

// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "vkStatus"

class VkDeveloperFragment : Fragment() {

    private var param1: String? = null
    private lateinit var devViewModel: VkDeveloperViewModel

    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View? {
        arguments?.let {
            param1 = it.getString(ARG_PARAM1)
        }
        devViewModel = ViewModelProvider(this).get(VkDeveloperViewModel::class.java)
        val root = inflater.inflate(R.layout.vkdeveloper_fragment, container, false)
        val textView: TextView = root.findViewById(R.id.vk_message)
        //devViewModel.text.observe(viewLifecycleOwner, Observer {
            textView.text = param1
        //})
        return root
    }
}