import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
<<<<<<< HEAD

import App from './App'
=======
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom'
import { Home } from './pages/home.jsx'
>>>>>>> 9a46186bb9e48daea7d74dd392900573f17c3a51

 
import { Layout } from './components/Layout.jsx'

createRoot(document.getElementById('root')).render(
  <StrictMode>
<<<<<<< HEAD
 <App/>
=======
     <Layout>
    <Router>
      
        <Routes>
          <Route path="/" element={<Home />} />
        </Routes>
     
    </Router>
    </Layout>
>>>>>>> 9a46186bb9e48daea7d74dd392900573f17c3a51
  </StrictMode>,
)