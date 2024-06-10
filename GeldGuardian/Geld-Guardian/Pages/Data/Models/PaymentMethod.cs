using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;

namespace Geld_Guardian.Pages.Data.Models
{
    [PrimaryKey("PaymentId")]
    public class PaymentMethod
    {
        public int PaymentId { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        // one to many relationship with Bill
        public ICollection<Bill> Bills { get; set; }

        public override string ToString()
        {
            return Name;
        }

    }
}
